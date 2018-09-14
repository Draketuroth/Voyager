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

#include <glm.hpp>

#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

#include <cassert>

using glm::vec3;
using glm::vec4;
using glm::mat4;

using Math::Vector3D;

const uint VERTEX_BYTE_SIZE = 8 * sizeof(float);

namespace Graphics
{
	GLRenderer::GLRenderer()
	{

	}

	bool GLRenderer::initialize()
	{
		_texture = new Texture();
		_texture->initialize("Textures\\uv_test.jpg");

		_width = 0;
		_height = 0;
		return true;
	}

	bool GLRenderer::shutdown()
	{
		_texture->shutdown();
		delete _texture;
		_texture = nullptr;

		_program = nullptr;

		return true;
	}

	void GLRenderer::update(float t)
	{

	}

	void GLRenderer::resize(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void GLRenderer::setProgram(ShaderProgram* program)
	{
		_program = program;
	}

	void GLRenderer::updateViewport(const int width, const int height)
	{
		_width = width;
		_height = height;
		glViewport(0, 0, _width, _height);
	}

	// Replaced paint event. 
	void GLRenderer::render(const Camera camera, Model* model)
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glm::mat4 mvp_matrix;
		glm::mat4 view_to_proj = glm::perspective(glm::radians(60.0f), ((float)_width) / _height, 0.1f, 20.f);
		glm::mat4 world_to_view = camera.getViewMatrix();
		glm::mat4 world_to_proj = view_to_proj * world_to_view;

		for (uint i = 0; i < _num_renderables; i++)
		{
			const Renderable& r = _renderables[i];

			vec3 eye_position = camera.getPosition();
			glUniform3fv(_program->_camera_position_uniform_location, 1, &eye_position[0]);

			vec4 ambient_light(0.05f, 0.05f, 0.05f, 1.0f);
			glUniform4fv(_program->_ambient_uniform_location, 1, &ambient_light[0]);

			vec3 light_position_world = model->light_position;
			glUniform3fv(_program->_light_uniform_location, 1, &light_position_world[0]);

			// Renderable Geometry.
			glBindTexture(GL_TEXTURE_2D, _texture->getID());
			glBindVertexArray(r._geometry_vao_ID);
			mvp_matrix = world_to_proj * r.transform;
			glUniformMatrix4fv(_program->_mvp_uniform_location, 1, GL_FALSE, &mvp_matrix[0][0]);
			glUniformMatrix4fv(_program->_world_uniform_location, 1, GL_FALSE, &r.transform[0][0]);
			glDrawElements(GL_TRIANGLES, r._geometry.num_indices, GL_UNSIGNED_SHORT, (void*)r._geometry_index_byte_offset);

			// Renderable Normal.
			// glBindVertexArray(_cube_normal_vao_ID);
			// glDrawElements(GL_LINES, _cube_num_normal_indices, GL_UNSIGNED_SHORT, (void*)_cube_normal_byte_offset);
			// glBindVertexArray(_cube_vao_ID);
			
		}
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

	void GLRenderer::addRenderable(Geometry geometry, glm::mat4 transform)
	{
		assert(_num_renderables != NUM_MAX_RENDERABLES);
		Renderable& r = _renderables[_num_renderables++];

		r._geometry = geometry;
		r._normal = GeometryGenerator::generateNormals(r._geometry);

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