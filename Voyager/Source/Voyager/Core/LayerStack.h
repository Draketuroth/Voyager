#ifndef VE_LAYERSTACK_H
#define VE_LAYERSTACK_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Layer.h"

#include <vector>

namespace VE
{
	namespace Core
	{
		class VOYAGER_API LayerStack
		{
		public:
			LayerStack();
			~LayerStack();

			bool empty();
			void pushLayer(Layer* layer);
			void pushOverlay(Layer* overlay);
			void popLayer(Layer* layer);
			void popOverlay(Layer* overlay);

			std::vector<Layer*>::iterator begin() { return _layers.begin(); }
			std::vector<Layer*>::iterator end() { return _layers.end(); }

		private:
			std::vector<Layer*> _layers;
			unsigned int _layerInsertIndex = 0;
		};
	}
};

#endif
