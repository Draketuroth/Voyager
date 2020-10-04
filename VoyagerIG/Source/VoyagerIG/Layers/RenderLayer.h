#ifndef IG_RENDER_LAYER_H
#define IG_RENDER_LAYER_H

#include "Voyager/Core/Layer.h"
#include "VoyagerIG/Systems/RenderSystem.h"

namespace IG { class Scene; }

namespace IG
{
	class RenderLayer : public VE::Core::Layer
	{
	public:
		RenderLayer(Scene* scene);
		~RenderLayer();

		void onUpdate(VE::Core::Timestep ts) override;

		void onEvent(VE::Event::Event& event) override;

	private:
		RenderLayer(const RenderLayer&);
		RenderLayer& operator=(const RenderLayer&);

		VE::Core::Ref<RenderSystem> _renderSystem;
		Scene* _scene;
	};
}

#endif