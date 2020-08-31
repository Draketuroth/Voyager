
#include "Voyager/IO/Parsing.h"
#include "Voyager/Core/Log.h"

#include <fstream>

#include <stb_image.h>

namespace VE
{
	namespace IO
	{
		std::string readFileToString(std::string file_name)
		{
			std::ifstream shader_input(file_name);
			if (!shader_input.good())
			{
				VE_CORE_WARN("File failed to load...");
				exit(1);
			}
			return std::string(
				std::istreambuf_iterator<char>(shader_input),
				std::istreambuf_iterator<char>());
		}

		Image::ImageData readImage(std::string path, bool flip) 
		{
			Image::ImageData img;
			img.path = path;

			flip ? stbi_set_flip_vertically_on_load(1) : stbi_set_flip_vertically_on_load(0);
			img.pixels = stbi_load(img.path.c_str(), &img.width, &img.height, &img.channels, STBI_rgb_alpha);
			VE_CORE_ASSERT(img.pixels, "Failed to load texture data!");

			return img;
		}
	}
}