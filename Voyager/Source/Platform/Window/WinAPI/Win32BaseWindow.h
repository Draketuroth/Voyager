#ifndef VE_WIN32_BASE_WINDOW_H
#define VE_WIN32_BASE_WINDOW_H

#define NOMINMAX

#include <windows.h>

namespace VE 
{
    namespace Platform 
    {
        namespace Window 
        {
            template <class T>
            class Win32BaseWindow 
            {
            public:
                // Base window callback to catch Win32 window creation and provide handling for
                // multiple windows - in the future. 
                static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
                {
                    T* pThis = NULL;

                    if (uMsg == WM_NCCREATE) 
                    {
                        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
                        pThis = (T*)pCreate->lpCreateParams;
                        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

                        pThis->hwnd = hwnd;
                    }
                    else 
                    {
                        pThis = (T*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
                    }
                    if (pThis) 
                    {
                        return pThis->handleMessage(uMsg, wParam, lParam);
                    }
                    else 
                    {
                        return DefWindowProc(hwnd, uMsg, wParam, lParam);
                    }
                }

                Win32BaseWindow() : hwnd(NULL) {}

                bool createWin32Window(LPCSTR lpWindowName,
                                       DWORD dwStyle,
                                       DWORD dwExStyle = 0,
                                       int x = CW_USEDEFAULT,
                                       int y = CW_USEDEFAULT,
                                       int width = CW_USEDEFAULT,
                                       int height = CW_USEDEFAULT,
                                       void* pData = 0,
                                       HWND hwndParent = 0,
                                       HMENU hMenu = 0) 
                {
                    WNDCLASS wc = { 0 };

                    wc.lpfnWndProc = T::WindowProc;
                    wc.hInstance = GetModuleHandle(NULL);
                    wc.lpszClassName = className();
                    wc.hIcon = (HICON)LoadImage(NULL, "Textures\\logo.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

                    RegisterClass(&wc);

                    hwnd = CreateWindowEx(
                        dwExStyle, className(), lpWindowName, dwStyle, x, y,
                        width, height, hwndParent, hMenu, GetModuleHandle(NULL), pData
                    );

                    return (hwnd ? true : false);
                }


            protected:
                virtual LPCSTR className() const = 0;
                virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lparam) = 0;

                HWND hwnd;
            };
        }
    }
}

#endif