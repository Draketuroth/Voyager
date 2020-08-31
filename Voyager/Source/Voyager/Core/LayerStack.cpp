
#include "LayerStack.h"

namespace VE
{
	namespace Core 
	{
		LayerStack::LayerStack()
		{

		}

		LayerStack::~LayerStack()
		{
			for (Layer* layer : _layers)
			{
				delete layer;
			}
		}

		void LayerStack::pushLayer(Layer* layer)
		{
			_layers.emplace(_layers.begin() + _layerInsertIndex, layer);
			_layerInsertIndex++;
			layer->onAttach();
		}

		void LayerStack::pushOverlay(Layer* overlay)
		{
			_layers.emplace_back(overlay);
			overlay->onAttach();
		}

		void LayerStack::popLayer(Layer* layer)
		{
			auto it = std::find(_layers.begin(), _layers.begin() + _layerInsertIndex, layer);
			if (it != _layers.end())
			{
				layer->onDetach();
				_layers.erase(it);
				_layerInsertIndex--;
			}
		}

		void LayerStack::popOverlay(Layer* overlay)
		{
			auto it = std::find(_layers.begin() + _layerInsertIndex, _layers.end(), overlay);
			if (it != _layers.end())
			{
				overlay->onDetach();
				_layers.erase(it);
			}
		}
	}
};