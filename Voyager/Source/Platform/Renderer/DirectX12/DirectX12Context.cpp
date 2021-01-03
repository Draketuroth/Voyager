
#include "Platform/Renderer/DirectX12/DirectX12Context.h"

#include "Voyager/Core/Log.h"

#include <dxgi1_4.h>
#include <dxgi1_6.h>

std::string getFeatureLevelString(D3D_FEATURE_LEVEL featureLevel)
{
    switch (featureLevel)
    {
    case D3D_FEATURE_LEVEL_1_0_CORE:
        return std::string("D3D_FEATURE_LEVEL_1_0_CORE");
    case D3D_FEATURE_LEVEL_9_1:
        return std::string("D3D_FEATURE_LEVEL_9_1");
    case D3D_FEATURE_LEVEL_9_2:
        return std::string("D3D_FEATURE_LEVEL_9_2");
    case D3D_FEATURE_LEVEL_9_3:
        return std::string("D3D_FEATURE_LEVEL_9_3");
    case D3D_FEATURE_LEVEL_10_0:
        return std::string("D3D_FEATURE_LEVEL_10_0");
    case D3D_FEATURE_LEVEL_10_1:
        return std::string("D3D_FEATURE_LEVEL_10_1");
    case D3D_FEATURE_LEVEL_11_0:
        return std::string("D3D_FEATURE_LEVEL_11_0");
    case D3D_FEATURE_LEVEL_11_1:
        return std::string("D3D_FEATURE_LEVEL_11_1");
    case D3D_FEATURE_LEVEL_12_0:
        return std::string("D3D_FEATURE_LEVEL_12_0");
    case D3D_FEATURE_LEVEL_12_1:
        return std::string("D3D_FEATURE_LEVEL_12_1");
    default:
        return std::string();
    }
}

namespace VE
{
	namespace Platform
	{
        namespace Renderer 
        {
            namespace DirectX
            {
                DirectX12Context::DirectX12Context() :
                    vendorInfo(),
                    useWarpDevice(false),
                    featureLevel(),
                    featureDataSupport()
                {

                }
                DirectX12Context::~DirectX12Context()
                {

                }
                bool DirectX12Context::init()
                {
                    featureLevel = D3D_FEATURE_LEVEL_12_1;
                    initializeDevice(featureLevel);
                    featureDataSupport = FeatureDataSupport(device);

                    VE_CORE_INFO("DirectX Info:");
                    VE_CORE_INFO("  Vendor: {0}", vendorInfo.vendor.c_str());
                    VE_CORE_INFO("  Renderer: {0}", "DirectX12");
                    VE_CORE_INFO("  Version: {0}", getFeatureLevelString(featureLevel).c_str());

                    // For full support matrix, consult the following diagram: https://en.wikipedia.org/wiki/Feature_levels_in_Direct3D
                    switch (featureDataSupport.options5.RaytracingTier)
                    {
                    case D3D12_RAYTRACING_TIER_NOT_SUPPORTED:
                        VE_CORE_INFO("Raytracing is not supported on this device");
                        break;
                    case D3D12_RAYTRACING_TIER_1_0:
                        VE_CORE_INFO("Raytracing Tier 1.0 is supported on this device");
                        break;
                    case D3D12_RAYTRACING_TIER_1_1:
                        VE_CORE_INFO("Raytracing Tier 1.1 is supported on this device");
                        break;
                    default:
                        break;
                    }

                    return true;
                }
                void DirectX12Context::swapBuffers()
                {

                }

                void DirectX12Context::initializeDevice(D3D_FEATURE_LEVEL featureLevel)
                {
                    UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
                    // Enable the debug layer (requires the Graphics Tools "optional feature").
                    // NOTE: Enabling the debug layer after device creation will invalidate the active device.
                    {
                        Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
                        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
                        {
                            debugController->EnableDebugLayer();

                            // Enable additional debug layers.
                            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
                        }
                    }
#endif

                    Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
                    ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));

                    if (useWarpDevice)
                    {
                        Microsoft::WRL::ComPtr<IDXGIAdapter> warpAdapter;
                        ThrowIfFailed(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));

                        ThrowIfFailed(D3D12CreateDevice(
                            warpAdapter.Get(),
                            featureLevel,
                            IID_PPV_ARGS(&device)
                        ));
                    }
                    else
                    {
                        Microsoft::WRL::ComPtr<IDXGIAdapter1> hardwareAdapter;
                        getHardwareAdapter(factory.Get(), &hardwareAdapter, featureLevel);

                        ThrowIfFailed(D3D12CreateDevice(
                            hardwareAdapter.Get(),
                            featureLevel,
                            IID_PPV_ARGS(&device)
                        ));
                    }
                }

                void DirectX12Context::getHardwareAdapter(IDXGIFactory1* pFactory, IDXGIAdapter1** pAdapter, D3D_FEATURE_LEVEL featureLevel, bool requestHighPerformanceAdapter)
                {
                    *pAdapter = nullptr;

                    Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;

                    Microsoft::WRL::ComPtr<IDXGIFactory6> factory6;
                    if (SUCCEEDED(pFactory->QueryInterface(IID_PPV_ARGS(&factory6))))
                    {
                        for (UINT adapterIndex = 0;
                            DXGI_ERROR_NOT_FOUND != factory6->EnumAdapterByGpuPreference(
                                adapterIndex,
                                requestHighPerformanceAdapter == true ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_UNSPECIFIED,
                                IID_PPV_ARGS(&adapter));
                            ++adapterIndex)
                        {
                            DXGI_ADAPTER_DESC1 desc;
                            adapter->GetDesc1(&desc);

                            char description[128];
                            char DefChar = ' ';
                            WideCharToMultiByte(CP_ACP, 0, desc.Description, -1, description, 128, &DefChar, NULL);
                            vendorInfo.vendor = std::string(description);

                            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                            {
                                // Don't select the Basic Render Driver adapter.
                                // If you want a software adapter, pass in "/warp" on the command line.
                                continue;
                            }

                            // Check to see whether the adapter supports Direct3D 12, but don't create
                            // the actual device yet.
                            if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), featureLevel, __uuidof(ID3D12Device), nullptr)))
                            {
                                break;
                            }
                        }

                    }
                    else
                    {
                        for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex)
                        {
                            DXGI_ADAPTER_DESC1 desc;
                            adapter->GetDesc1(&desc);

                            char description[128];
                            char DefChar = ' ';
                            WideCharToMultiByte(CP_ACP, 0, desc.Description, -1, description, 128, &DefChar, NULL);
                            vendorInfo.vendor = std::string(description);

                            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                            {
                                // Don't select the Basic Render Driver adapter.
                                // If you want a software adapter, pass in "/warp" on the command line.
                                continue;
                            }

                            // Check to see whether the adapter supports Direct3D 12, but don't create
                            // the actual device yet.
                            if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), featureLevel, __uuidof(ID3D12Device), nullptr)))
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}