//============================================================================
// # VOYAGER ENGINE #
// Name: ShaderProgram.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: OpenGL shader program container.
//============================================================================

#include <Graphics/Shading/ShaderProgram.h>
#include <Graphics/Shading/DebugHelper.h>

#include <QtCore/qdebug.h>

namespace Graphics
{
	ShaderProgram::ShaderProgram()
	{
		qDebug() << "Created ShaderProgram";
	}

	ShaderProgram::~ShaderProgram()
	{
		qDebug() << "Destroyed ShaderProgram";
	}

	bool ShaderProgram::initialize()
	{
		_id = glCreateProgram();
		return true;
	}

	void ShaderProgram::initializeUniforms()
	{
		_mvp_uniform_location = glGetUniformLocation(_id, "model_to_projection_matrix");
		_world_uniform_location = glGetUniformLocation(_id, "model_to_world_matrix");
		_ambient_uniform_location = glGetUniformLocation(_id, "ambient_light");
		_light_uniform_location = glGetUniformLocation(_id, "light_position_world");
		_camera_position_uniform_location = glGetUniformLocation(_id, "eye_position_world");
		_diffuse_color_uniform_location = glGetUniformLocation(_id, "diffuse_color");
	}

	bool ShaderProgram::shutdown()
	{
		_vertex_shader = nullptr;
		_geometry_shader = nullptr;
		_fragment_shader = nullptr;

		glUseProgram(0);
		glDeleteProgram(_id);

		return true;
	}

	bool ShaderProgram::link()
	{
		glLinkProgram(_id);

		if (!checkProgramStatus(_id))
		{
			return false;
		}

		return true;
	}

	void ShaderProgram::use()
	{
		glUseProgram(_id);
	}

	GLuint ShaderProgram::getID() const
	{
		return _id;
	}

	bool ShaderProgram::setVertexShader(const std::shared_ptr<Shader>& shader)
	{
		if (shader->getType() == GL_VERTEX_SHADER)
		{
			_vertex_shader = shader;
			glAttachShader(_id, _vertex_shader->getID());
		}
		return false;
	}

	bool ShaderProgram::setGeometryShader(const std::shared_ptr<Shader>& shader)
	{
		if (shader->getType() == GL_GEOMETRY_SHADER)
		{
			_geometry_shader = shader;
			glAttachShader(_id, _geometry_shader->getID());
			return true;
		}
		return false;
	}

	bool ShaderProgram::setFragmentShader(const std::shared_ptr<Shader>& shader)
	{
		if (shader->getType() == GL_FRAGMENT_SHADER)
		{
			_fragment_shader = shader;
			glAttachShader(_id, _fragment_shader->getID());
			return true;
		}
		return false;
	}

	bool ShaderProgram::checkProgramStatus(GLuint program_id)
	{
		return checkStatus(program_id, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
	}
}