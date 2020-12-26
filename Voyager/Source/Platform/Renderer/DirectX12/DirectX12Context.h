#ifndef VE_DIRECTX12_CONTEXT_H
#define VE_DIRECTX12_CONTEXT_H

#include "Voyager/Renderer/GraphicsContext.h"

namespace VE
{
	namespace Platform
	{
		namespace DirectX
		{
			class DirectX12Context : public Rendering::GraphicsContext
			{
			public:
				DirectX12Context();

				virtual void init() override;
				virtual void swapBuffers() override;

			private:
				
			};
		}
	}
}

#endif