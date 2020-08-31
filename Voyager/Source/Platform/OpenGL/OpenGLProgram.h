#ifndef VE_OPENGL_PROGRAM_H
#define VE_OPENGL_PROGRAM_H

#include <memory>

#include "OpenGLShader.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			struct OpenGLProgramHandle
			{
				OpenGLProgramHandle() :
					_publicID(0),
					_internalID(0)
				{
				}

				GLuint _publicID;
				GLuint _internalID;
			};

			class OpenGLProgram
			{
			public:

				static OpenGLProgramHandle initialize();
				static void remove(GLuint id);

				static bool link(OpenGLProgramHandle& handle);
				static void use(const OpenGLProgramHandle handle);

				static bool status(GLuint id);

			};
		}
	}
}

#endif