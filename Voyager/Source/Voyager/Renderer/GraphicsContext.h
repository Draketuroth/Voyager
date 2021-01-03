#ifndef VE_GRAPHICS_CONTEXT_H
#define VE_GRAPHICS_CONTEXT_H

namespace VE
{
	namespace Rendering 
	{
		class GraphicsContext
		{
		public:
			virtual ~GraphicsContext() {}

			virtual bool init() = 0;
			virtual void swapBuffers() = 0;
		};
	}
}

#endif