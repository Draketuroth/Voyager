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
		Scene* scene;
		VE::Core::Layer* baseLayer;
		VE::Core::Layer* resourceLayer;
		VE::Core::Layer* renderLayer;
	};
}

#endif