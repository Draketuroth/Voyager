#ifndef VE_MATERIAL_STANDARD_H
#define VE_MATERIAL_STANDARD_H

#include "Voyager/Math/Vector/Vector3.h"

#include "Voyager/Renderer/Material.h"

#include <unordered_map>
#include <map>

static const unsigned int TEXTURESLOTS = 4;

namespace VE { namespace Rendering { class Texture2D; } }

namespace VE 
{
	namespace Rendering 
	{
		class StandardMaterial : public Rendering::Material
		{
		public:
			StandardMaterial()
			{

			}

			~StandardMaterial() 
			{
				for (unsigned int index = 0; index < TEXTURESLOTS; index++) 
				{
					_textures[index] = nullptr;
				}
			}

			virtual void setShaderIdentifier(unsigned int shaderIdentifier) override
			{
				_shaderIdentifier = shaderIdentifier;
			}

			virtual void setTexture(Texture2D* texture, Material::TextureSlot slot) override 
			{ 
				unsigned int index = static_cast<unsigned int>(slot);
				if (index < TEXTURESLOTS) 
				{
					_textures[index] = texture;
					_active[index] = true;
				}
			}

			virtual void resetTextureSlot(TextureSlot slot) 
			{
				unsigned int index = static_cast<unsigned int>(slot);
				_textures[index] = nullptr;
				_active[index] = false;
			}

			virtual bool hasTexture(TextureSlot slot) 
			{
				return _active[static_cast<unsigned int>(slot)];
			}

			virtual Texture2D* getTexture(Material::TextureSlot slot) override
			{ 
				unsigned int index = static_cast<unsigned int>(slot);
				if (index < TEXTURESLOTS) 
				{
					if (_textures[index] != nullptr) 
					{
						return _textures[index];
					}
				}
				return nullptr;
			}

			virtual unsigned int getShaderIdentifier() const override
			{
				return _shaderIdentifier;
			}

		private:
			bool _active[TEXTURESLOTS] = { false };
			Texture2D* _textures[TEXTURESLOTS] = { nullptr };
			unsigned int _shaderIdentifier;
		};
	}
}

#endif