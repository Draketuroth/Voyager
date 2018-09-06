//============================================================================
// # VOYAGER ENGINE #
// Name: GLWindow.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 30, 2018
// Description: Qt-based OpenGL window
//============================================================================

#include <gl/glew.h>

#include <Qt3DInput/qmouseevent.h>
#include <Qt3DInput/qkeyevent.h>
#include <QtCore/qdebug.h>

#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

#include <Graphics/GL/glassert.h>
#include <Graphics/Window/GLWindow.h>
#include <Graphics/Primitives/Vertex.h>
#include <Graphics/Primitives/GeometryGenerator.h>

using Math::Vector3D;
using glm::vec3;
using glm::vec4;
using glm::mat4;

const uint VERTEX_BYTE_SIZE = 9 * sizeof(float);

namespace Graphics
{
	static void infoGL()
	{
		glCheckError();
		const GLubyte *str;
		std::cout << "OpenGL Status" << std::endl;
		str = glGetString(GL_RENDERER);
		std::cout << "Renderer : " << str << std::endl;
		str = glGetString(GL_VENDOR);
		std::cout << "Vendor : " << str << std::endl;
		str = glGetString(GL_VERSION);
		std::cout << "OpenGL Version : " << str << std::endl;
		str = glGetString(GL_SHADING_LANGUAGE_VERSION);
		std::cout << "GLSL Version : " << str << std::endl;
		glCheckError();
	}

	GLWindow::GLWindow()
	{

	}

	GLWindow::~GLWindow()
	{

	}

	bool GLWindow::initialize()
	{
		return true;
	}

	bool GLWindow::shutdown()
	{
		glDeleteBuffers(1, &_buffer_ID);

		glDeleteShader(_vertex_shader_ID);
		glDeleteShader(_fragment_shader_ID);

		glUseProgram(0);
		glDeleteProgram(_program_ID);
		return true;
	}

	void GLWindow::sendDataToOpenGL()
	{
		// Generate cube geometry.
		Geometry cube = GeometryGenerator::makeCube();
		Geometry cube_normals = GeometryGenerator::generateNormals(cube);

		// Generate plane geometry.
		Geometry plane = GeometryGenerator::makePlane();
		Geometry plane_normals = GeometryGenerator::generateNormals(plane);

		// Generate buffer for all data.
		glGenBuffers(1, &_buffer_ID);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer_ID);
		glBufferData(GL_ARRAY_BUFFER, 
			cube.vertexBufferSize() + cube.indexBufferSize() +
			plane.vertexBufferSize() + plane.indexBufferSize() +
			cube_normals.vertexBufferSize() + cube_normals.indexBufferSize() +
			plane_normals.vertexBufferSize() + plane_normals.indexBufferSize() , 0, GL_STATIC_DRAW);

		GLsizeiptr current_offset = 0;

		// Send cube data and offset.
		glBufferSubData(GL_ARRAY_BUFFER, current_offset, cube.vertexBufferSize(), cube.vertices);
		current_offset += cube.vertexBufferSize();
		_cube_index_byte_offset = current_offset;
		glBufferSubData(GL_ARRAY_BUFFER, current_offset, cube.indexBufferSize(), cube.indices);
		current_offset += cube.indexBufferSize();

		// Send plane data and offset.
		glBufferSubData(GL_ARRAY_BUFFER, current_offset, plane.vertexBufferSize(), plane.vertices);
		current_offset += plane.vertexBufferSize();
		_plane_index_byte_offset = current_offset;
		glBufferSubData(GL_ARRAY_BUFFER, current_offset, plane.indexBufferSize(), plane.indices);
		current_offset += plane.indexBufferSize();

		// Send cube normals and offset.
		glBufferSubData(GL_ARRAY_BUFFER, current_offset, cube_normals.vertexBufferSize(), cube_normals.vertices);
		current_offset += cube_normals.vertexBufferSize();
		_cube_normal_byte_offset = current_offset;
		glBufferSubData(GL_ARRAY_BUFFER, current_offset, cube_normals.indexBufferSize(), cube_normals.indices);
		current_offset += cube_normals.indexBufferSize();

		// Send plane normals and offset.
		glBufferSubData(GL_ARRAY_BUFFER, current_offset, plane_normals.vertexBufferSize(), plane_normals.vertices);
		current_offset += plane_normals.vertexBufferSize();
		_plane_normal_byte_offset = current_offset;
		glBufferSubData(GL_ARRAY_BUFFER, current_offset, plane_normals.indexBufferSize(), plane_normals.indices);
		current_offset += plane_normals.indexBufferSize();

		_cube_num_indices = cube.num_indices;
		_cube_num_normal_indices = cube_normals.num_indices;

		_plane_num_indices = plane.num_indices;
		_plane_num_normal_indices = plane_normals.num_indices;

		// Generate vertex array objects.
		glGenVertexArrays(1, &_cube_vao_ID);
		glGenVertexArrays(1, &_plane_vao_ID);

		// Generate normals vertex array objects.
		glGenVertexArrays(1, &_cube_normal_vao_ID);
		glGenVertexArrays(1, &_plane_normal_vao_ID);

		// Bind vertex array objects.
		glBindVertexArray(_cube_vao_ID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer_ID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 6));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_buffer_ID);

		glBindVertexArray(_plane_vao_ID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer_ID);
		GLuint plane_byte_offset = cube.vertexBufferSize() + cube.indexBufferSize();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)plane_byte_offset);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(plane_byte_offset + sizeof(float) * 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(plane_byte_offset + sizeof(float) * 6));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_ID);

		// Bind normal vertex array objects.
		glBindVertexArray(_cube_normal_vao_ID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer_ID);
		GLuint cube_normal_byte_offset = plane_byte_offset + plane.vertexBufferSize() + plane.indexBufferSize();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)cube_normal_byte_offset);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(cube_normal_byte_offset + sizeof(float) * 3));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_ID);

		glBindVertexArray(_plane_normal_vao_ID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer_ID);
		GLuint plane_normal_byte_offset = cube_normal_byte_offset + cube_normals.vertexBufferSize() + cube_normals.indexBufferSize();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)plane_normal_byte_offset);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(plane_normal_byte_offset + sizeof(float) * 3));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_ID);

		cube.release();
		plane.release();
	}

	void GLWindow::initializeShaders()
	{
		_vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);	// VSO
		_fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);	// FSO

		const char* adapter[1];
		std::string temp = _shader.readShaderCode("Shaders\\vertex.glsl").c_str();
		adapter[0] = temp.c_str();
		glShaderSource(_vertex_shader_ID, 1, adapter, 0);
		temp = _shader.readShaderCode("Shaders\\fragment.glsl").c_str();
		adapter[0] = temp.c_str();
		glShaderSource(_fragment_shader_ID, 1, adapter, 0);

		glCompileShader(_vertex_shader_ID);
		glCompileShader(_fragment_shader_ID);

		if (!checkShaderStatus(_vertex_shader_ID) || !checkShaderStatus(_fragment_shader_ID))
		{
			return;
		}

		_program_ID = glCreateProgram();
		glAttachShader(_program_ID, _vertex_shader_ID);
		glAttachShader(_program_ID, _fragment_shader_ID);

		// Explicitly bind the vertex attributes.
		// layout(location = N) is not necessary in shader.
		// glBindAttribLocation(_program_ID, 1, "position");

		// Or let the linker handle the binding automatically.
		// layout(location = N) is required in shader.
		glLinkProgram(_program_ID);

		if (!checkProgramStatus(_program_ID))
		{
			return;
		}

		// If the linker binds the attributes, make sure to query and verify their location!
		GLint position_location = glGetAttribLocation(_program_ID, "vertex_position");
		GLint color_location = glGetAttribLocation(_program_ID, "vertex_color");
		GLint transform_location = glGetAttribLocation(_program_ID, "vertex_normal");

		glUseProgram(_program_ID);
	}

	bool GLWindow::checkShaderStatus(GLuint shader_id)
	{
		return checkStatus(shader_id, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
	}

	bool GLWindow::checkProgramStatus(GLuint program_id)
	{
		return checkStatus(program_id, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
	}

	bool GLWindow::checkStatus(
		GLuint object_id,
		PFNGLGETSHADERIVPROC object_property_getter,
		PFNGLGETSHADERINFOLOGPROC info_log_func,
		GLenum status_type)
	{
		// iv = integer vector. We are just passing one.
		GLint status;
		object_property_getter(object_id, status_type, &status);
		if (status != GL_TRUE)
		{
			GLint info_log_length;
			object_property_getter(object_id, GL_INFO_LOG_LENGTH, &info_log_length);
			GLchar* buffer = new GLchar[info_log_length];

			GLsizei buffer_size;
			info_log_func(object_id, info_log_length, &buffer_size, buffer);
			qDebug() << buffer;

			delete[] buffer;
			return false;
		}
		return true;
	}

	void GLWindow::initializeGL()
	{
		setMouseTracking(true);
		glewInit();
		glEnable(GL_DEPTH_TEST);
		infoGL();
		sendDataToOpenGL();
		initializeShaders();

		// Only necessary to do once after the shaders have been initialized! 
		_mvp_uniform_location = glGetUniformLocation(_program_ID, "model_to_projection_matrix");
		_world_uniform_location = glGetUniformLocation(_program_ID, "model_to_world_matrix");
		_ambient_uniform_location = glGetUniformLocation(_program_ID, "ambient_light");
		_light_uniform_location = glGetUniformLocation(_program_ID, "light_position_world");
		_camera_position_uniform_location = glGetUniformLocation(_program_ID, "eye_position_world");
	}

	void GLWindow::paintGL()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width(), height());

		mat4 mvp_matrix;
		mat4 view_to_proj = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 20.f);
		mat4 world_to_view = _camera.getViewMatrix();
		mat4 world_to_proj = view_to_proj * world_to_view;

		vec3 eye_position = _camera.getPosition();
		glUniform3fv(_camera_position_uniform_location, 1, &eye_position[0]);

		vec4 ambient_light(0.05f, 0.05f, 0.05f, 1.0f);
		glUniform4fv(_ambient_uniform_location, 1, &ambient_light[0]);

		vec3 light_position_world(0.0f, 1.0f, 0.0f);
		glUniform3fv(_light_uniform_location, 1, &light_position_world[0]);

		// Cube. 
		glBindVertexArray(_cube_vao_ID);
		mat4 cube_1_model_to_world = 
			glm::translate(vec3(-3.0f, 1.0f, -2.0f)) *
			glm::rotate(0.0f, vec3(1.0f, 0.0f, 0.0f));
		mvp_matrix = world_to_proj * cube_1_model_to_world;
		glUniformMatrix4fv(_mvp_uniform_location, 1, GL_FALSE, &mvp_matrix[0][0]);
		glUniformMatrix4fv(_world_uniform_location, 1, GL_FALSE, &cube_1_model_to_world[0][0]);
		glDrawElements(GL_TRIANGLES, _cube_num_indices, GL_UNSIGNED_SHORT, (void*)_cube_index_byte_offset);
		glBindVertexArray(_cube_normal_vao_ID);
		glDrawElements(GL_LINES, _cube_num_normal_indices, GL_UNSIGNED_SHORT, (void*)_cube_normal_byte_offset);

		glBindVertexArray(_cube_vao_ID);
		mat4 cube_2_model_to_world =
			glm::translate(vec3(3.0f, 1.0f, -2.0f)) *
			glm::rotate(0.0f, vec3(0.0f, 1.0f, 0.0f));
		mvp_matrix = world_to_proj * cube_2_model_to_world;
		glUniformMatrix4fv(_mvp_uniform_location, 1, GL_FALSE, &mvp_matrix[0][0]);
		glUniformMatrix4fv(_world_uniform_location, 1, GL_FALSE, &cube_2_model_to_world[0][0]);
		glDrawElements(GL_TRIANGLES, _cube_num_indices, GL_UNSIGNED_SHORT, (void*)_cube_index_byte_offset);
		glBindVertexArray(_cube_normal_vao_ID);
		glDrawElements(GL_LINES, _cube_num_normal_indices, GL_UNSIGNED_SHORT, (void*)_cube_normal_byte_offset);

		// Plane.
		glBindVertexArray(_plane_vao_ID);
		mat4 plane_model_to_world = glm::translate(vec3(0.5f, 0.0f, 0.0f));
		mvp_matrix = world_to_proj * plane_model_to_world;
		glUniformMatrix4fv(_mvp_uniform_location, 1, GL_FALSE, &mvp_matrix[0][0]);
		glUniformMatrix4fv(_world_uniform_location, 1, GL_FALSE, &plane_model_to_world[0][0]);
		glDrawElements(GL_TRIANGLES, _plane_num_indices, GL_UNSIGNED_SHORT, (void*)_plane_index_byte_offset);
		glBindVertexArray(_plane_normal_vao_ID);
		glDrawElements(GL_LINES, _plane_num_normal_indices, GL_UNSIGNED_SHORT, (void*)_plane_normal_byte_offset);
	}

	void GLWindow::mouseMoveEvent(QMouseEvent* e)
	{
		_camera.mouseUpdate(glm::vec2(e->x(), e->y()));
		repaint();
	}

	void GLWindow::closeEvent(QCloseEvent *e)
	{
		shutdown();
	}

	void GLWindow::keyPressEvent(QKeyEvent *e)
	{
		switch (e->key())
		{
		case Qt::Key::Key_W:
			_camera.moveForward();
			break;
		case Qt::Key::Key_S:
			_camera.moveBackward();
			break;
		case Qt::Key::Key_A:
			_camera.strafeLeft();
			break;
		case Qt::Key::Key_D:
			_camera.strafeRight();
			break;
		case Qt::Key::Key_R:
			_camera.moveUp();
			break;
		case Qt::Key::Key_F:
			_camera.moveDown();
			break;
		}
		repaint();
	}
}