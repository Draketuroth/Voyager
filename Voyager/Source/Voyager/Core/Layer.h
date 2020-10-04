#ifndef VE_LAYER_H
#define VE_LAYER_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Timestep.h"
#include "Voyager/Event/Event.h"

namespace VE
{
	namespace Core 
	{
		class VOYAGER_API Layer
		{
		public:
			Layer(const std::string& name = "Layer");
			virtual ~Layer();

			virtual void onAttach() {}
			virtual void onDetach() {}
			virtual void onUpdate(Timestep delta, Timestep timeMs) {}
			virtual void onImGuiRender() {}
			virtual void onEvent(Event::Event& event) {}

			inline const std::string& getName() const { return _debugName; }

		protected:
			std::string _debugName;
		};
	}
};

#endif