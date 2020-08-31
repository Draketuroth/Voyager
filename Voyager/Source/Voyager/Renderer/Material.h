#ifndef VE_MATERIAL_H
#define VE_MATERIAL_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Resource.h"

#include "Voyager/IO/ImportSettings.h"

namespace VE { namespace Rendering { class Texture2D; } }

namespace VE 
{
	namespace Rendering
	{
		class VOYAGER_API Material : public Core::Resource
		{
		public:
			enum class TextureSlot : unsigned int
			{
				AMBIENT,
				DIFFUSE,
				NORMAL,
				SPECULAR
			};
			enum class MaterialType : unsigned int 
			{
				STANDARD,
				PBR
			};

			virtual ~Material() {};

			virtual void setShaderIdentifier(unsigned int shaderIdentifier) = 0;
			virtual void setTexture(VE::Rendering::Texture2D* texture, TextureSlot slot) = 0;
			virtual void resetTextureSlot(TextureSlot slot) = 0;
			virtual bool hasTexture(TextureSlot slot) = 0;

			virtual Texture2D* getTexture(TextureSlot slot) = 0;
			virtual unsigned int getShaderIdentifier() const = 0;

			static void createResource(Material** resource, const std::string path, VE::IO::Setting flags);
			static Material* create();
		};
	}
}

#endif