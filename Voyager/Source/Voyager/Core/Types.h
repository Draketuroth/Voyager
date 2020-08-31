#ifndef VE_TYPES_H
#define VE_TYPES_H

#include <cstdint>
#include <bitset>

#include "Voyager/Core/Core.h"

namespace VE 
{
	namespace Core
	{
		// ECS
		using Entity = std::uint32_t;
		const Entity MAX_ENTITIES = 5000;

		using ComponentType = std::uint8_t;
		const ComponentType MAX_COMPONENTS = 32;

		using Signature = std::bitset<MAX_COMPONENTS>;

		struct EntityInfo
		{
			VE::Core::Entity id;
			bool wireframe = false;
		};
	}
}

#endif