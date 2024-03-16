#include <windows.h>
#include <tchar.h>
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class
    WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("D3D Example"), NULL};
    RegisterClassEx(&wc);

    // Create the window
    HWND hWnd = CreateWindow(_T("D3D Example"), _T("Direct3D Example"),
                             WS_OVERLAPPEDWINDOW, 100, 100, 800, 600,
                             NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    IDirect3D9 *pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the Direct3D device
    IDirect3DDevice9 *pd3dDevice = NULL;
    if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                  D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                  &d3dpp, &pd3dDevice)))
    {
        return 0;
    }

    // Main message loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // Render here
            pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
            pd3dDevice->BeginScene();
            // Draw stuff here
            pd3dDevice->EndScene();
            pd3dDevice->Present(NULL, NULL, NULL, NULL);
        }
    }

    // Clean up
    if (pd3dDevice)
        pd3dDevice->Release();
    if (pD3D)
        pD3D->Release();
    UnregisterClass(_T("D3D Example"), wc.hInstance);
    return 0;
}
