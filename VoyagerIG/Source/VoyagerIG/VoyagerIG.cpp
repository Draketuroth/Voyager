#include <Voyager.h>

#include "VoyagerIG/VoyagerIG.h"
#include "VoyagerIG/Scene.h"

#include "VoyagerIG/Layers/SceneLayer.h"
#include "VoyagerIG/Layers/ResourceLayer.h"
#include "VoyagerIG/Layers/RenderLayer.h"

#include <iostream>

VE::Core::Application* VE::Core::CreateApplication()
{
	return new IG::VoyagerIG();
}

void VE::Core::printApplicationArgs() 
{
	std::cerr << "Usage: " << "VoyagerIG" << " <option(s)>\n"
		<< "Options:\n"
		<< "\t--help\t\tShow this help message\n"
		<< "\t--renderapi\t\tSet renderer api at start ['OpenGL', 'DirectX', 'Vulcan']\n"
		<< "\t--verbose\t\tPrint debug messages / developer messages\n"
		<< std::endl;
}

namespace IG 
{
	VoyagerIG::VoyagerIG()
	{
		_scene = new Scene();

		_baseLayer = new SceneLayer(_scene);
		pushLayer(_baseLayer);

		_resourceLayer = new ResourceLayer(_scene, _window->getWidth(), _window->getHeight());
		pushLayer(_resourceLayer);

		_renderLayer = new RenderLayer(_scene);
		pushLayer(_renderLayer);
	}

	VoyagerIG::~VoyagerIG()
	{
		// Will trigger OnDetach for each layer.
		popLayer(_renderLayer);
		popLayer(_resourceLayer);
		popLayer(_baseLayer);

		delete _renderLayer;
		delete _resourceLayer;
		delete _baseLayer;
	}
}
