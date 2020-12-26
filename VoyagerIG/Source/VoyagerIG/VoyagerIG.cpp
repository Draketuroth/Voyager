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
		<< "\t--renderapi\t\tSet renderer api at start ['OpenGL', 'DirectX12', 'Vulcan']\n"
		<< "\t--verbose\t\tPrint debug messages / developer messages\n"
		<< std::endl;
}

namespace IG 
{
	VoyagerIG::VoyagerIG()
	{
		/*
		scene = new Scene();

		baseLayer = new SceneLayer(scene);
		pushLayer(baseLayer);

		resourceLayer = new ResourceLayer(scene, windowInterface->getWidth(), windowInterface->getHeight());
		pushLayer(resourceLayer);

		renderLayer = new RenderLayer(scene);
		pushLayer(renderLayer);
		*/
	}

	VoyagerIG::~VoyagerIG()
	{
		
		// Will trigger OnDetach for each layer.
		/*
		popLayer(renderLayer);
		popLayer(resourceLayer);
		popLayer(baseLayer);

		delete renderLayer;
		delete resourceLayer;
		delete baseLayer;
		*/
		
	}
}
