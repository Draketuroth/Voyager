#ifndef VE_TEXTURE_H
#define VE_TEXTURE_H

#include "Voyager/Core/Core.h"

#include "Voyager/Image/ImageData.h"

#include "Voyager/Core/Resource.h"
#include "Voyager/IO/ImportSettings.h"

#include <cstdint>
#include <string>

namespace VE 
{
	namespace Rendering 
	{
		class VOYAGER_API Texture2D : public Core::Resource
		{
		public:
			virtual ~Texture2D() = default;

			virtual std::uint32_t getWidth() const = 0;
			virtual std::uint32_t getHeight() const = 0;

			static void createResource(Texture2D** resource, const std::string path, VE::IO::Setting flags);
			static Texture2D* create(const VE::Image::ImageData& data);
		};
	}
}

#endif