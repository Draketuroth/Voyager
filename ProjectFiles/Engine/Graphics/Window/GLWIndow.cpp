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
using glm::mat4;

GLuint arrow_num_indices;
GLuint cube_num_indices;

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

		glDeleteBuffers(1, &_vertex_buffer_ID);
		glDeleteBuffers(1, &_vertex_buffer_ID);

		glDeleteShader(_vertex_shader_ID);
		glDeleteShader(_fragment_shader_ID);

		glUseProgram(0);
		glDeleteProgram(_program_ID);
		return true;
	}

	void GLWindow::sendDataToOpenGL()
	{
		// Cube.
		Geometry cube = GeometryGenerator::makeCube();
		cube_num_indices = cube.num_indices;

		Geometry arrow = GeometryGenerator::makeArrow();
		arrow_num_indices = arrow.num_indices;

		glGenBuffers(1, &_vertex_buffer_ID);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_ID);
		glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize() + arrow.vertexBufferSize(), 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, cube.vertexBufferSize(), cube.vertices);
		glBufferSubData(GL_ARRAY_BUFFER, cube.vertexBufferSize(), arrow.vertexBufferSize(), arrow.vertices);
		
		glGenBuffers(1, &_index_buffer_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indexBufferSize() + arrow.indexBufferSize(), 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, cube.indexBufferSize(), cube.indices);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, cube.indexBufferSize(), arrow.indexBufferSize(), arrow.indices);

		glGenVertexArrays(1, &_cube_vao_ID);
		glGenVertexArrays(1, &_arrow_vao_ID);

		// All cube bind and attrib functions stored in vertex array object.
		glBindVertexArray(_cube_vao_ID);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_ID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_ID);

		glBindVertexArray(_arrow_vao_ID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_ID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(cube.vertexBufferSize()));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(cube.vertexBufferSize() + sizeof(float) * 3));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_ID);

		_arrow_index_buffer_offset = cube.indexBufferSize();

		cube.release();
		arrow.release();
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
		glBindAttribLocation(_program_ID, 1, "position");

		// Or let the linker handle the binding automatically.
		// layout(location = N) is required in shader.
		glLinkProgram(_program_ID);

		if (!checkProgramStatus(_program_ID))
		{
			return;
		}

		// If the linker binds the attributes, make sure to query and verify their location!
		GLint position_location = glGetAttribLocation(_program_ID, "position");
		GLint color_location = glGetAttribLocation(_program_ID, "vertex_color");
		GLint transform_location = glGetAttribLocation(_program_ID, "transform");

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
		_mvp_uniform_location = glGetUniformLocation(_program_ID, "mvp_matrix");
	}

	void GLWindow::paintGL()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width(), height());

		mat4 mvp_matrix;
		mat4 view_to_proj = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 10.f);
		mat4 world_to_view = _camera.getViewMatrix();
		mat4 world_to_proj = view_to_proj * world_to_view;

		// Cube. 
		glBindVertexArray(_cube_vao_ID);
		mat4 cube_1_model_to_world = 
			glm::translate(vec3(-1.0f, 0.0f, -3.0f)) *
			glm::rotate(36.0f, vec3(1.0f, 0.0f, 0.0f));
		mvp_matrix = world_to_proj * cube_1_model_to_world;
		glUniformMatrix4fv(_mvp_uniform_location, 1, GL_FALSE, &mvp_matrix[0][0]);
		glDrawElements(GL_TRIANGLES, cube_num_indices, GL_UNSIGNED_SHORT, 0);

		mat4 cube_2_model_to_world =
			glm::translate(vec3(1.0f, 0.0f, -3.75f)) *
			glm::rotate(126.0f, vec3(0.0f, 1.0f, 0.0f));
		mvp_matrix = world_to_proj * cube_2_model_to_world;
		glUniformMatrix4fv(_mvp_uniform_location, 1, GL_FALSE, &mvp_matrix[0][0]);
		glDrawElements(GL_TRIANGLES, cube_num_indices, GL_UNSIGNED_SHORT, 0);

		// Arrow.
		glBindVertexArray(_arrow_vao_ID);
		mat4 arrow_model_to_world = glm::translate(vec3(1.0f, 0.0f, -3.0f));
		mvp_matrix = world_to_proj * arrow_model_to_world;
		glUniformMatrix4fv(_mvp_uniform_location, 1, GL_FALSE, &mvp_matrix[0][0]);
		glDrawElements(GL_TRIANGLES, arrow_num_indices, GL_UNSIGNED_SHORT, (void*)_arrow_index_buffer_offset);
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