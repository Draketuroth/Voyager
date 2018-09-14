//============================================================================
// # VOYAGER ENGINE #
// Name: Shader.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 30, 2018
// Description: OpenGL shader wrapper.
//============================================================================

#include <fstream>
#include <QtCore/qdebug.h>

#include <Graphics/Shading/DebugHelper.h>
#include <Graphics/Shading/Shader.h>

namespace Graphics
{
	Shader::Shader()
	{

	}

	Shader::~Shader()
	{

	}

	GLuint Shader::getID() const
	{
		return _id;
	}

	GLenum Shader::getType() const
	{
		return _type;
	}

	bool Shader::initialize(const char * file_name, const GLenum type)
	{
		_id = glCreateShader(type);
		_type = type;

		const char* adapter[1];
		std::string temp = readShaderCode(file_name).c_str();
		adapter[0] = temp.c_str();

		glShaderSource(_id, 1, adapter, 0);

		glCompileShader(_id);

		if (!checkShaderStatus(_id))
		{
			return false;
		}
		return true;
	}

	bool Shader::shutdown()
	{
		glDeleteShader(_id);
		return true;
	}

	std::string Shader::readShaderCode(const char* file_name)
	{
		std::ifstream shader_input(file_name);
		if (!shader_input.good())
		{
			qDebug() << "File failed to load..." << file_name;
			exit(1);
		}
		return std::string(
			std::istreambuf_iterator<char>(shader_input),
			std::istreambuf_iterator<char>());
	}

	bool Shader::checkShaderStatus(GLuint shader_id)
	{
		return checkStatus(shader_id, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
	}

}