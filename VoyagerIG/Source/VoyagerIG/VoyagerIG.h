#ifndef MV_MODELVIEWER_H
#define MV_MODELVIEWER_H

#include <Voyager.h>

namespace IG { class Scene; }
namespace VE { namespace Core { class Layer; } }

namespace IG
{
	class VoyagerIG : public VE::Core::Application
	{
	public:
		VoyagerIG();
		~VoyagerIG();

	private:
		Scene* _scene;
		VE::Core::Layer* _baseLayer;
		VE::Core::Layer* _resourceLayer;
		VE::Core::Layer* _renderLayer;
	};
}

#endif