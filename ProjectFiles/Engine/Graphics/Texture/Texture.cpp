//============================================================================
// # VOYAGER ENGINE #
// Name: Texture.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 14, 2018
// Description: OpenGL texture wrapper.
//============================================================================

#include <Graphics/Texture/Texture.h>
#include <QtCore/qdebug.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Graphics
{
	Texture::Texture()
	{

	}

	Texture::~Texture()
	{

	}

	GLuint Texture::getID() const
	{
		return _id;
	}

	bool Texture::initialize(const char * file_name)
	{
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* data = stbi_load(file_name, &_width, &_height, &_num_channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			stbi_image_free(data);
			qDebug() << "Failed to load texture";
			return false;
		}

		stbi_image_free(data);
		return true;
	}

	bool Texture::shutdown()
	{
		glDeleteTextures(1, &_id);
		return false;
	}
}


