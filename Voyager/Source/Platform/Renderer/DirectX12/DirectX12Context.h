#ifndef VE_DIRECTX12_CONTEXT_H
#define VE_DIRECTX12_CONTEXT_H

#include "Voyager/Renderer/GraphicsContext.h"
#include "Platform/Renderer/HardwareInfo.h"

#include "Platform/Renderer/DirectX12/DXHelper.h"
#include "Platform/Renderer/DirectX12/DirectX12FeatureSupport.h"

#include <d3d12.h>
#include <dxgi.h>
#include <wrl/client.h>

namespace VE
{
	namespace Platform
	{
		namespace Renderer 
		{
			namespace DirectX
			{
				class DirectX12Context : public Rendering::GraphicsContext
				{
				public:
					DirectX12Context();
					~DirectX12Context();

					virtual bool init() override;
					virtual void swapBuffers() override;

				private:
					void initializeDevice(D3D_FEATURE_LEVEL featureLevel);

					void getHardwareAdapter(
						IDXGIFactory1* pFactory,
						IDXGIAdapter1** pAdapter,
						D3D_FEATURE_LEVEL featureLevel,
						bool requestHighPerformanceAdapter = false);

					GraphicsVendorInfo vendorInfo;

					bool useWarpDevice;
					ID3D12Device5* device;

					D3D_FEATURE_LEVEL featureLevel;
					FeatureDataSupport featureDataSupport;
				};
			}
		}
	}
}

#endif