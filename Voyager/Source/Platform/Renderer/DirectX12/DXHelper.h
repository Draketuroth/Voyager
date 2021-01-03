#ifndef VE_DX_HELPER_H
#define VE_DX_HELPER_H

#include <stdexcept>
#include <string>
#include <winerror.h>
#include <stdio.h>
#include <wchar.h>

namespace VE 
{
    namespace Platform 
    {
        namespace Renderer 
        {
            namespace DirectX
            {
                inline std::string HrToString(HRESULT hr)
                {
                    char buf[64] = {};
                    sprintf_s(buf, "HRESULT of 0x%08X", static_cast<unsigned int>(hr));
                    return std::string(buf);
                }

                class HrException : public std::runtime_error
                {
                public:
                    HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), _hr(hr) {}
                    HRESULT error() const { return _hr; }
                private:
                    const HRESULT _hr;
                };

                inline void ThrowIfFailed(HRESULT hr)
                {
                    if (FAILED(hr))
                    {
                        throw HrException(hr);
                    }
                }
            }
        }
    }
}

#endif