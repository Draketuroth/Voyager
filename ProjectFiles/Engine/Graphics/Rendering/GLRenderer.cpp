//============================================================================
// # VOYAGER ENGINE #
// Name: GLRenderer.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: OpenGL based renderer.
//============================================================================

#include <Graphics/Rendering/GLRenderer.h>
#include <Graphics/Primitives/GeometryGenerator.h>
#include <Graphics/GL/glassert.h>

#include <Graphics/Datatypes/Model.h>

#include <Graphics/Camera/Camera.h>

#include <Graphics/Texture/Texture.h>

#include <Math/Utilz.h>

#include <glm.hpp>

#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

#include <QtCore/qdebug.h>

#include <cassert>

using glm::vec3;
using glm::vec4;
using glm::mat4;

using Math::Vector3D;

const uint VERTEX_BYTE_SIZE = 8 * sizeof(float);

vec3 color;

namespace Graphics
{
	GLRenderer::GLRenderer()
	{
		qDebug() << "Created GLRenderer";
	}

	GLRenderer::~GLRenderer()
	{
		qDebug() << "Destroyed GLRenderer";
	}

	int GLRenderer::initialize()
	{
		_texture = std::make_shared<Texture>();
		_texture->initialize("Textures\\uv_test.jpg");

		_width = 0;
		_height = 0;

		color = vec3(0.0f, 0.0f, 0.0f);

		return 0;
	}

	void GLRenderer::update(float t)
	{

	}

	void GLRenderer::resize(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void GLRenderer::setProgram(std::unique_ptr<ShaderProgram> program)
	{
		_program = std::move(program);
	}

	void GLRenderer::setModelView(Model* model)
	{
		_model = model;
	}

	void GLRenderer::setActiveCamera(Camera * camera)
	{
		_active_camera = camera;
	}

	void GLRenderer::updateViewport(const int width, const int height)
	{
		_width = width;
		_height = height;
		_active_camera->setAspectRatio(((float)_width) / _height);
		glViewport(0, 0, _width, _height);
	}

	void GLRenderer::updateView()
	{
		view_to_proj = _active_camera->getProjectionMatrix();
		world_to_view = _active_camera->getViewMatrix();
		world_to_proj = view_to_proj * world_to_view;
	}

	// Replaced paint event. 
	int GLRenderer::render()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		for (uint i = 0; i < _num_renderables; i++)
		{
			const Renderable& r = _renderables[i];

			float lerp_factor = _model->lerp_value;

			color = vec3(Math::lerp(0.0f, 1.0f, lerp_factor), Math::lerp(0.0f, 1.0f, 1 - lerp_factor), 0.0f);
			glUniform3fv(_program->_diffuse_color_uniform_location, 1, &color[0]);
			
			vec3 eye_position = _active_camera->getPosition();
			glUniform3fv(_program->_camera_position_uniform_location, 1, &eye_position[0]);

			vec4 ambient_light(0.05f, 0.05f, 0.05f, 1.0f);
			glUniform4fv(_program->_ambient_uniform_location, 1, &ambient_light[0]);

			vec3 light_position_world = _model->light_position;
			glUniform3fv(_program->_light_uniform_location, 1, &light_position_world[0]);

			// Renderable Geometry.
			glBindTexture(GL_TEXTURE_2D, _texture->getID());
			glBindVertexArray(r._geometry_vao_ID);
			glm::mat4 mvp_matrix = world_to_proj * r.transform;
			glUniformMatrix4fv(_program->_mvp_uniform_location, 1, GL_FALSE, &mvp_matrix[0][0]);
			glUniformMatrix4fv(_program->_world_uniform_location, 1, GL_FALSE, &r.transform[0][0]);
			glDrawElements(r._geometry.render_mode, r._geometry.num_indices, GL_UNSIGNED_SHORT, (void*)r._geometry_index_byte_offset);

			// Renderable Normal.
			// glBindVertexArray(_cube_normal_vao_ID);
			// glDrawElements(GL_LINES, _cube_num_normal_indices, GL_UNSIGNED_SHORT, (void*)_cube_normal_byte_offset);
			// glBindVertexArray(_cube_vao_ID);
			
		}

		return 0;
	}

	Geometry* GLRenderer::addGeometry(
		Vertex* vertices, uint num_vertices,
		ushort* indices, uint num_indices, GLenum render_mode)
	{
		assert(_num_geometries != NUM_MAX_GEOMETRIES);
		Geometry& g = _geometries[_num_geometries++];
		g.vertices = vertices;
		g.indices = indices;
		g.num_vertices = num_vertices;
		g.num_indices = num_indices;
		g.render_mode = render_mode;
		return &g;
	}

	void GLRenderer::addRenderable(Geometry g, Transform t)
	{
		assert(_num_renderables != NUM_MAX_RENDERABLES);
		Renderable& r = _renderables[_num_renderables++];

		r._geometry = g;
		r._geometry.render_mode = GL_TRIANGLES;

		r._normal = GeometryGenerator::generateNormals(r._geometry);
		r._normal.render_mode = GL_LINES;

		glm::mat4 transform = 
			glm::translate(vec3(t.p[0], t.p[1], t.p[2])) *
			glm::rotate(t.r[0], vec3(t.r[1], t.r[2], t.r[3])) *
			glm::scale(vec3(t.s[0], t.s[1], t.s[2]));
		r.transform = transform;

		setupBuffer(r._geometry_buffer_ID, r._geometry);
		r._geometry_index_byte_offset = r._geometry.vertexBufferSize();

		setupBuffer(r._normal_buffer_ID, r._normal);
		r._normal_index_byte_offset = r._normal.vertexBufferSize();

		setupGeometryVAO(r._geometry_vao_ID, r._geometry_buffer_ID);
		setupNormalVAO(r._normal_vao_ID, r._normal_buffer_ID);

	}

	void GLRenderer::setupBuffer(GLuint &buffer_id, Geometry g)
	{
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ARRAY_BUFFER, g.vertexBufferSize() + g.indexBufferSize(), 0, GL_STATIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, g.vertexBufferSize(), g.vertices);
		glBufferSubData(GL_ARRAY_BUFFER, g.vertexBufferSize(), g.indexBufferSize(), g.indices);
	}

	void GLRenderer::setupNormalVAO(GLuint & vao_id, GLuint buffer_id)
	{
		glGenVertexArrays(1, &vao_id);

		glBindVertexArray(vao_id);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
	}

	void GLRenderer::setupGeometryVAO(GLuint &vao_id, GLuint buffer_id)
	{
		glGenVertexArrays(1, &vao_id);

		// Bind vertex array objects.
		glBindVertexArray(vao_id);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 6));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
	}

}