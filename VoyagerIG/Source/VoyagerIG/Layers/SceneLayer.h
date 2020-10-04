#ifndef IG_SCENE_LAYER_H
#define IG_SCENE_LAYER_H

#include "Voyager/Core/Layer.h"

namespace IG { class Scene; }

namespace VE { namespace Rendering { class Texture2D; } }

namespace IG
{
	class SceneLayer : public VE::Core::Layer
	{
	public:
		SceneLayer(Scene* scene);
		~SceneLayer();

		void onUpdate(VE::Core::Timestep delta, VE::Core::Timestep timeMs) override;

		void onEvent(VE::Event::Event& event) override;

		void showEntityWidgetFunc(bool* status);

		void showAboutWidgetFunc(bool* status);

		virtual void onImGuiRender() override;

	private:
		SceneLayer(const SceneLayer&);
		SceneLayer& operator=(const SceneLayer&);

		Scene* _scene;

		VE::Rendering::Texture2D* _logo;
		bool _imGuiMenuActive = false;
	};
}

#endif