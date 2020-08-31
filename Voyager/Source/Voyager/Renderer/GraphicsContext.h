#ifndef VE_GRAPHICS_CONTEXT_H
#define VE_GRAPHICS_CONTEXT_H

namespace VE
{
	namespace Rendering 
	{
		class GraphicsContext
		{
		public:
			virtual void init() = 0;
			virtual void swapBuffers() = 0;
		};
	}
}

#endif