#ifndef VE_OPENGL_SHADER_H
#define VE_OPENGL_SHADER_H

#include "Voyager/Renderer/Shader.h"

#include "Platform/Renderer/OpenGL/OpenGLStatus.h"

#include "Voyager/Core/Core.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			class VOYAGER_API OpenGLShaderUtility
			{
			public:

				// static void bind(const unsigned int* program);
				// static void unbind();
				static bool compile(VE::Rendering::ShaderHandle& handle);
				static int translateShaderType(Rendering::ShaderType type);
			};

			class OpenGLShader : public VE::Rendering::Shader
			{
			public:
				OpenGLShader(const std::string& filepath);
				virtual ~OpenGLShader();

				virtual bool status() const override;

				virtual VE::Rendering::ShaderHandle& getShaderHandle() override;

				bool initialize(const char* path);

			private:
				VE::Rendering::ShaderHandle _handle;

			};
		}
	}
}

#endif
