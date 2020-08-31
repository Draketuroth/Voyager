#ifndef VE_IMAGEDATA_H
#define VE_IMAGEDATA_H

#include <string>

namespace VE 
{
	namespace Image
	{
		struct ImageData
		{
			int width;
			int height;
			int channels;
			std::string path;
			unsigned char* pixels;
		};
	}
}


#endif