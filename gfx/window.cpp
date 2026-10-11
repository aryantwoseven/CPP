//cl /EHsc /std:c++17 window.cpp /link /SUBSYSTEM:WINDOWS user32.lib gdi32.lib

#define NOMINMAX
#include <windows.h>
#include "bresenham-line.hpp"

static Renderer renderer;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    const char CLASS_NAME[] = "RendererWindow";

    WNDCLASSA wc = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    RegisterClassA(&wc);

    // CLIENT AREA Size
    DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    RECT rc = {0, 0, WIDTH, HEIGHT};
    AdjustWindowRect(&rc, style, FALSE);

    HWND hwnd = CreateWindowExA(0, CLASS_NAME, "Line", style,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
        nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) return 0;
    ShowWindow(hwnd, nCmdShow);

    // describe the pixel buffer to Windows
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = WIDTH;
    bmi.bmiHeader.biHeight      = -HEIGHT;   // negative = top-down
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    bool running = true;
    while (running) {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) running = false;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        renderer.bres_draw();

        HDC hdc = GetDC(hwnd);
        StretchDIBits(hdc,
            0, 0, WIDTH, HEIGHT,
            0, 0, WIDTH, HEIGHT,
            renderer.s1.color, &bmi,
            DIB_RGB_COLORS, SRCCOPY);
        ReleaseDC(hwnd, hdc);

        Sleep(16);   // ~60 fps
    }
    return 0;
}
