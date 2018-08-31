//============================================================================
// # VOYAGER ENGINE #
// Name: GLWindow.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 30, 2018
// Description: Qt-based OpenGL window
//============================================================================

#include <gl/glew.h>
#include <Graphics/GL/glassert.h>
#include <Graphics/Window/GLWindow.h>
#include <QtCore/qdebug.h>

#include <gtc/matrix_transform.hpp>

#include <Graphics/Primitives/Vertex.h>
#include <Graphics/Primitives/GeometryGenerator.h>

using Math::Vector3D;
using glm::vec3;
using glm::mat4;

namespace Graphics
{
	GLuint num_indices;

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

	void GLWindow::sendDataToOpenGL()
	{
		Geometry cube = GeometryGenerator::makeCube();
		num_indices = cube.num_indices;

		GLuint vertex_buffer_ID;
		glGenBuffers(1, &vertex_buffer_ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_ID);
		glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize(), cube.vertices, GL_STATIC_DRAW);

		// Stride is the distance from the beginning of the first attribute to the next occurence of it. 
		// Stride = 0 means that data is tightly packed.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

		GLuint index_buffer_ID;
		glGenBuffers(1, &index_buffer_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indexBufferSize(), cube.indices, GL_STATIC_DRAW);

		cube.release();
	}

	void GLWindow::initializeShaders()
	{
		GLuint vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);	// VSO
		GLuint fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);	// FSO

		const char* adapter[1];
		std::string temp = _shader.readShaderCode("Shaders\\vertex.glsl").c_str();
		adapter[0] = temp.c_str();
		glShaderSource(vertex_shader_ID, 1, adapter, 0);
		temp = _shader.readShaderCode("Shaders\\fragment.glsl").c_str();
		adapter[0] = temp.c_str();
		glShaderSource(fragment_shader_ID, 1, adapter, 0);

		glCompileShader(vertex_shader_ID);
		glCompileShader(fragment_shader_ID);

		if (!checkShaderStatus(vertex_shader_ID) || !checkShaderStatus(fragment_shader_ID))
		{
			return;
		}

		_program_ID = glCreateProgram();
		glAttachShader(_program_ID, vertex_shader_ID);
		glAttachShader(_program_ID, fragment_shader_ID);
		glLinkProgram(_program_ID);

		if (!checkProgramStatus(_program_ID))
		{
			return;
		}

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
		glewInit();
		glEnable(GL_DEPTH_TEST);
		infoGL();
		sendDataToOpenGL();
		initializeShaders();
	}

	void GLWindow::paintGL()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width(), height());

		mat4 model_matrix = glm::translate(mat4(1.0f), vec3(+0.0f, +0.0f, -3.0f));
		mat4 projection_matrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 10.0f);

		GLint model_matrix_uniform_location = glGetUniformLocation(_program_ID, "model_matrix");
		GLint projection_matrix_uniform_location = glGetUniformLocation(_program_ID, "projection_matrix");

		glUniformMatrix4fv(model_matrix_uniform_location, 1, GL_FALSE, &model_matrix[0][0]);
		glUniformMatrix4fv(projection_matrix_uniform_location, 1, GL_FALSE, &projection_matrix[0][0]);

		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_SHORT, 0);
	}
}