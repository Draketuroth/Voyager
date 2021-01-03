#ifndef VE_DIRECTX12_FEATURE_SUPPORT_H
#define VE_DIRECTX12_FEATURE_SUPPORT_H

#include "Platform/BasicTypes.h"
#include "Platform/Renderer/DirectX12/DXHelper.h"

#include <d3d12.h>

namespace VE
{
    namespace Platform
    {
        namespace Renderer
        {
            namespace DirectX
            {
                struct FeatureDataSupport
                {
                    FeatureDataSupport():
                    options(),
                    options1(),
                    options2(), 
                    options3(),
                    options4(),
                    options5(),
                    options6(),
                    options7() 
                    {}

                    FeatureDataSupport(ID3D12Device* device) 
                    {
                        ThrowIfFailed(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS,  &options,  sizeof(options)));
                        ThrowIfFailed(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS1, &options1, sizeof(options1)));
                        ThrowIfFailed(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS2, &options2, sizeof(options2)));
                        ThrowIfFailed(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS3, &options3, sizeof(options3)));
                        ThrowIfFailed(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS4, &options4, sizeof(options4)));
                        ThrowIfFailed(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &options5, sizeof(options5)));
                        ThrowIfFailed(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS6, &options6, sizeof(options6)));
                        ThrowIfFailed(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &options7, sizeof(options7)));
                    }

                    D3D12_FEATURE_DATA_D3D12_OPTIONS  options;
                    D3D12_FEATURE_DATA_D3D12_OPTIONS1 options1;
                    D3D12_FEATURE_DATA_D3D12_OPTIONS2 options2;
                    D3D12_FEATURE_DATA_D3D12_OPTIONS3 options3;
                    D3D12_FEATURE_DATA_D3D12_OPTIONS4 options4;
                    D3D12_FEATURE_DATA_D3D12_OPTIONS5 options5;
                    D3D12_FEATURE_DATA_D3D12_OPTIONS6 options6;
                    D3D12_FEATURE_DATA_D3D12_OPTIONS7 options7;
                };
            }
        }

    }
}

#endif