#ifndef VE_GRAPHICS_TEXTURE_MANAGER_H
#define VE_GRAPHICS_TEXTURE_MANAGER_H

#include <Graphics/Texture/Texture.h>

#include <memory>
#include <unordered_map>
#include <string>

namespace Graphics
{
	class TextureManager
	{
	public:
		static std::shared_ptr<Texture> Acquire(const std::string& name);
		static void Remove();
	private:
		static std::unordered_map<std::string, std::shared_ptr<Texture>> texture_ptrs;
	};

}

#endif
