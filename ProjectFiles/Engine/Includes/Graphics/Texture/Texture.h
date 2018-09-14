//============================================================================
// # VOYAGER ENGINE #
// Name: Texture.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 14, 2018
// Description: OpenGL texture wrapper.
//============================================================================

#ifndef VE_GRAPHICS_TEXTURE_H
#define VE_GRAPHICS_TEXTURE_H

#include <gl/glew.h>

#if defined DLL_EXPORT_GRAPHICS
#define DECLDIR_R __declspec(dllexport)
#else
#define DECLDIR_R __declspec(dllimport)
#endif

namespace Graphics
{
	class DECLDIR_R Texture
	{
	public:

		Texture();
		~Texture();

		GLuint getID() const;

		bool initialize(const char* file_name);
		bool shutdown();

	private:

		GLuint _id;

		int _width;
		int _height;
		int _num_channels;
	};
}

#endif
