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
		Geometry _cube = GeometryGenerator::makeCube();

		_vertex_buffer_ID;
		glGenBuffers(1, &_vertex_buffer_ID);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_ID);
		glBufferData(GL_ARRAY_BUFFER, _cube.vertexBufferSize(), _cube.vertices, GL_STATIC_DRAW);

		// Stride is the distance from the beginning of the first attribute to the next occurence of it. 
		// Stride = 0 means that data is tightly packed.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

		glEnableVertexAttribArray(1);
		// glVertexAttrib3f(1, 0, 1, 0);	// Disable attribute 1 and force static data for all vertices rather than streaming. 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

		_index_buffer_ID;
		glGenBuffers(1, &_index_buffer_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _cube.indexBufferSize(), _cube.indices, GL_STATIC_DRAW);

		_cube.release();

		GLuint transformation_matrix_ID;
		glGenBuffers(1, &transformation_matrix_ID);
		glBindBuffer(GL_ARRAY_BUFFER, transformation_matrix_ID);

		glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * 2, 0, GL_DYNAMIC_DRAW);

		int offset = 0;
		for (int i = 2; i <= 5; i++)
		{
			glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * offset));
			glEnableVertexAttribArray(i);
			glVertexAttribDivisor(i, 1);
			offset += 4;
		}
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
	}

	void GLWindow::paintGL()
	{
		mat4 projection_matrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 10.0f);

		mat4 transforms[] =
		{
			projection_matrix * _camera.getViewMatrix() * glm::translate(vec3(-1.0f, +0.0f, -3.0f)) * glm::rotate(glm::radians(36.0f), vec3(+1.0f, +0.0f, 0.0f)),
			projection_matrix * _camera.getViewMatrix() * glm::translate(vec3(1.0f, +0.0f, -3.75f)) *  glm::rotate(glm::radians(126.0f), vec3(+0.0f, +1.0f, 0.0f)),
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(transforms), transforms, GL_DYNAMIC_DRAW);

		glClearColor(0, 0, 0, 1);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width(), height());
		
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, 2);

	}

	void GLWindow::mouseMoveEvent(QMouseEvent* e)
	{
		_camera.mouseUpdate(glm::vec2(e->x(), e->y()));
		repaint();
	}

	void GLWindow::closeEvent(QCloseEvent *bar)
	{
		shutdown();
	}
}