#include "Voyager/Renderer/Shader.h"
#include "Voyager/Renderer/Renderer.h"

#include "Platform/Renderer/OpenGL/OpenGLShader.h"

#include "Platform/Renderer/RendererAPIHandler.h"
#include "Platform/APIType.h"

#include <fstream>

#include <glad/glad.h>

namespace VE
{
	namespace Rendering {

		void Shader::createResource(Shader** resource, const std::string path, VE::IO::Setting flags)
		{
			switch (Platform::Renderer::RendererAPIHandler::getAPI())
			{
				case Platform::API::RenderAPI::None:
					VE_CORE_ASSERT(false, "RendererAPI::None is not supported");
					break;
				case Platform::API::RenderAPI::OpenGL:
					*resource = new Platform::OpenGL::OpenGLShader(path);
			}

			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
		}

		Shader* Shader::create(const std::string& filepath)
		{
			switch (Platform::Renderer::RendererAPIHandler::getAPI())
			{
				case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RendererAPI::None is not supported");
				case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLShader(filepath);
			}

			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}

		bool Shader::getNameTypePair(TypePair& tp, std::string path)
		{
			std::string fileStr = path;

			// Get name.
			size_t delimiter = fileStr.find_last_of('\\');
			if (delimiter == std::string::npos)
			{
				std::cout << "Failed to acquire shader name from path" << std::endl;
				return false;
			}
			tp._name = fileStr.substr(delimiter + 1);

			// Get type.
			delimiter = tp._name.find_last_of('.');
			if (delimiter == std::string::npos)
			{
				std::cout << "Failed to acquire shader type from path" << std::endl;
				return false;
			}
			std::string extension = tp._name.substr(delimiter + 1);
			if (extension == "vert")
			{
				tp._type = ShaderType::VERTEX;
			}
			else if (extension == "frag")
			{
				tp._type = ShaderType::FRAGMENT;
			}
			else
			{
				std::cout << "Failed to set shader type from extension" << std::endl;
				return false;
			}

			return true;
		}

	}
}
