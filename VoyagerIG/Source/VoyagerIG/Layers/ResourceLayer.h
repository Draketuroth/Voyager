#ifndef IG_RESOURCE_LAYER_H
#define IG_RESOURCE_LAYER_H

#include "Voyager/Core/Layer.h"
#include "Voyager/IO/FileNotifier.h"

namespace IG { class Scene; }

namespace IG
{
	class ResourceLayer : public VE::Core::Layer
	{
	public:
		ResourceLayer(Scene* scene, unsigned int winSizeX, unsigned int winSizeY);
		~ResourceLayer();

		void onUpdate(VE::Core::Timestep ts) override;

		void onEvent(VE::Event::Event& event) override;

	private:
		ResourceLayer(const ResourceLayer&);
		ResourceLayer& operator=(const ResourceLayer&);

		Scene* _scene;
		VE::Core::Scope<VE::IO::FileNotifier> _fileNotifier;
	};
}

#endif