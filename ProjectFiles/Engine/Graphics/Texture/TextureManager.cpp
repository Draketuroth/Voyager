
#include <Graphics/Texture/TextureManager.h>

namespace Graphics
{
	std::shared_ptr<Texture> Graphics::TextureManager::Acquire(const std::string & name)
	{
		const auto i = texture_ptrs.find(name);
		if (i != texture_ptrs.end())
		{
			return i->second;
		}
		else
		{
			auto tex = std::make_shared<Texture>();
			tex->initialize(name.c_str());
			texture_ptrs.insert({ name, tex });
			return tex;
		}
	}
	void TextureManager::Remove()
	{
		for(auto i = texture_ptrs.begin(); i != texture_ptrs.end();)
		{
			if(i->second.unique())
			{
				i = texture_ptrs.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
}
