#include "Voyager/Renderer/Shader.h"
#include "Platform/Renderer/OpenGL/OpenGLShader.h"
#include "Platform/Renderer/OpenGL/OpenGLStatus.h"

#include <fstream>
#include <iostream>

#include "Voyager/IO//Parsing.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			/*
			void OpenGLShaderUtility::bind(const unsigned int* program)
			{
				glUseProgram(*program);
			}
			void OpenGLShaderUtility::unbind()
			{
				glUseProgram(0);
			}
			*/
			bool OpenGLShaderUtility::compile(Rendering::ShaderHandle& handle)
			{
				const char* adapter[1];
				std::string temp = VE::IO::readFileToString(handle._path);
				adapter[0] = temp.c_str();

				glShaderSource(handle._id, 1, adapter, 0);
				glCompileShader(handle._id);

				if (!OpenGLStatus::status(handle._id, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS))
				{
					glDeleteShader(handle._id);
					return false;
				}
				return true;
			}

			int OpenGLShaderUtility::translateShaderType(Rendering::ShaderType type)
			{
				switch (type)
				{
				case VE::Rendering::ShaderType::NONE:
					return 0;
				case VE::Rendering::ShaderType::VERTEX:
					return GL_VERTEX_SHADER;
				case VE::Rendering::ShaderType::GEOMETRY:
					return GL_GEOMETRY_SHADER;
				case VE::Rendering::ShaderType::FRAGMENT:
					return GL_FRAGMENT_SHADER;
				default:
					return 0;
				}
				return 0;
			}

			OpenGLShader::OpenGLShader(const std::string& filepath)
			{
				initialize(filepath.c_str());
			}
			OpenGLShader::~OpenGLShader()
			{
				glDeleteShader(_handle._id);
			}

			Rendering::ShaderHandle& OpenGLShader::getShaderHandle()
			{
				return _handle;
			}

			bool OpenGLShader::status() const
			{
				return OpenGLStatus::status(_handle._id, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
			}

			bool OpenGLShader::initialize(const char* path)
			{
				_handle._path = path;

				Rendering::TypePair tp;
				if (getNameTypePair(tp, _handle._path))
				{
					_handle._name = tp._name;
					_handle._type = tp._type;
					_handle._id = glCreateShader(OpenGLShaderUtility::translateShaderType(_handle._type));
					_handle._hash = (int32_t)std::hash<std::string>()(_handle._name) & 0x7FFF;

					if (!OpenGLShaderUtility::compile(_handle))
					{
						std::cout << "Failed to compile shader " << tp._name << std::endl;
						return false;
					}

				}
				else
				{
					std::cout << "GLShader::initialize could not construct typepair" << std::endl;
				}

				return true;
			}
		}
	}
}