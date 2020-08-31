
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Voyager/Core/Log.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			OpenGLTexture2D::OpenGLTexture2D(const VE::Image::ImageData& data) : Texture2D()
			{
				_refCount = 1;

				_width = data.width;
				_height = data.height;

				glCreateTextures(GL_TEXTURE_2D, 1, &_textureID);
				glTextureStorage2D(_textureID, 1, GL_RGBA8, _width, _height);

				glTextureParameteri(_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTextureParameteri(_textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTextureSubImage2D(_textureID, 0, 0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, data.pixels);

				// stbi_image_free(data.pixels);
			}
			OpenGLTexture2D::~OpenGLTexture2D()
			{
				glDeleteTextures(1, &_textureID);
			}
			void OpenGLTexture2D::bind(std::uint32_t slot) const
			{
				glBindTextureUnit(slot, _textureID);
			}

			void OpenGLTexture2D::reset(std::uint32_t slot) const
			{
				glBindTextureUnit(slot, 0);
			}
		}
	}
}