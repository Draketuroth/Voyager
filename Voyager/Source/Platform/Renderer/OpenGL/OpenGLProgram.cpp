#include "Platform/Renderer/OpenGL/OpenGLProgram.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			OpenGLProgramHandle OpenGLProgram::initialize()
			{
				OpenGLProgramHandle handle;
				handle._internalID = glCreateProgram();
				return handle;
			}

			void OpenGLProgram::remove(GLuint id)
			{
				glUseProgram(0);
				glDeleteProgram(id);
			}

			bool OpenGLProgram::link(OpenGLProgramHandle& handle)
			{
				glLinkProgram(handle._internalID);

				if (!status(handle._internalID))
				{
					handle._publicID = 0;
					return false;
				}
				handle._publicID = handle._internalID;

				return true;
			}

			void OpenGLProgram::use(const OpenGLProgramHandle handle)
			{
				glUseProgram(handle._publicID);
			}

			bool OpenGLProgram::status(GLuint id)
			{
				return OpenGLStatus::status(id, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
			}
		}
	}
}