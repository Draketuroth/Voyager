#ifndef VE_PARSER_H
#define VE_PARSER_H

#include <tuple>
#include <string>

#include "Voyager/Core/Core.h"
#include "Voyager/Image/ImageData.h"

namespace VE
{
	namespace IO
	{
		enum class FileStatus { CREATED, MODIFIED, ERASED };

		VOYAGER_API std::string readFileToString(std::string file_name);
		VOYAGER_API VE::Image::ImageData readImage(std::string path, bool flip = false);
	}
}

#endif