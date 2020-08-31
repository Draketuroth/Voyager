#ifndef VE_OPENGL_TEXTURE_H
#define VE_OPENGL_TEXTURE_H

#include "Voyager/Renderer/Texture.h"

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			class OpenGLTexture2D : public Rendering::Texture2D
			{
			public:
				OpenGLTexture2D(const VE::Image::ImageData& data);
				virtual ~OpenGLTexture2D();

				virtual unsigned int getTextureId() { return _textureID; }
				virtual std::uint32_t getWidth() const override { return _width; }
				virtual std::uint32_t getHeight() const override { return _height; }

				virtual void bind(std::uint32_t slot = 0) const;

				virtual void reset(std::uint32_t slot = 0) const;

			private:
				std::uint32_t _width;
				std::uint32_t _height;
				unsigned int _textureID;

			};
		}
	}
}

#endif