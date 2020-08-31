#ifndef VE_IMGUI_LAYER_H
#define VE_IMGUI_LAYER_H

#include "Voyager/Core/Layer.h"

#include "Voyager/Event/ApplicationEvent.h"
#include "Voyager/Event/KeyEvent.h"
#include "Voyager/Event/MouseEvent.h"

namespace VE
{
	class VOYAGER_API ImGuiLayer : public Core::Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();

	private:
		float _time = 0.0f;
	};
};

#endif