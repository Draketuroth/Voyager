#ifndef VE_OBSERVER_H
#define VE_OBSERVER_H

#include "Voyager/Event/Event.h"

namespace VE 
{
	namespace Event 
	{
		class Observer 
		{
			virtual void handle(const Event& e) = 0;
		};
	}
}

#endif