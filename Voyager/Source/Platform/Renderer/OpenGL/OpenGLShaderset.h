#ifndef VE_OPENGL_SHADERSET_H
#define VE_OPENGL_SHADERSET_H

#include <map>
#include <vector>

#include "Voyager/Renderer/Shaderset.h"

#include "Platform/Renderer/OpenGL/OpenGLProgram.h"

#include "Voyager/IO/Parsing.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL
		{
			class VOYAGER_API OpenGLShaderSet : public Rendering::ShaderSet
			{
			public:
				OpenGLShaderSet(std::vector<Rendering::Shader*> shaders);
				~OpenGLShaderSet();

				GLuint* addProgramFromShaders();

				// void update(Publisher* pub, void* msg = 0);
				// void updatePrograms(bool& refreshFlag);

			private:

				// Lookup table for program with matching set of shaders.
				std::map<std::vector<const VE::Rendering::TypePair*>, OpenGLProgramHandle> _programs;

				// Map shaders to handles in order to reuse shared shaders.
				std::map<VE::Rendering::TypePair, OpenGLShader*>  _shaders;

				// std::vector<VE::Rendering::TypePair> _updatedShaders;
			};
		}
	}
}

#endif
