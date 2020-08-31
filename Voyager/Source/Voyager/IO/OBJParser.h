#ifndef VE_OBJPARSER_H
#define VE_OBJPARSER_H

#include "Voyager/Core/Core.h"
#include "Voyager/Geometry/GeometryData.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

namespace VE 
{
	namespace IO 
	{
		namespace OBJ 
		{
			VE::Geometry::GeometryData VOYAGER_API parse(const std::string& path);
		}
	}
}

#endif