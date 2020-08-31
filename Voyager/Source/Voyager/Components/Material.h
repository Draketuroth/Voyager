#ifndef VE_COMPONENT_MATERIAL_H
#define VE_COMPONENT_MATERIAL_H

#include "Voyager/Renderer/Material.h"
#include "Voyager/Renderer/Texture.h"

namespace VE
{
	namespace Components
	{
		struct Material
		{
		public:
			Material() { _material = nullptr; }

			void setMaterialResourcePointer(VE::Rendering::Material* materialPtr)
			{
				_material = materialPtr;
			}

			VE::Rendering::Material* getMaterial()
			{
				return _material;
			}

			unsigned int getResourceHandle()
			{
				return _material->getHandle();
			}

			void setShaderIdentifier(unsigned int shaderIdentifier) 
			{
				_material->setShaderIdentifier(shaderIdentifier);
			}

			void setTexture(Rendering::Texture2D* texture, Rendering::Material::TextureSlot slot)
			{
				_material->setTexture(texture, slot);
			}

			void resetTextureSlot(Rendering::Material::TextureSlot slot)
			{
				_material->resetTextureSlot(slot);
			}

			bool hasTexture(Rendering::Material::TextureSlot slot)
			{
				return _material->hasTexture(slot);
			}

			VE::Rendering::Texture2D* getTexture(Rendering::Material::TextureSlot slot)
			{
				return _material->getTexture(slot);
			}

		private:
			VE::Rendering::Material* _material;
		};
	}
}

#endif