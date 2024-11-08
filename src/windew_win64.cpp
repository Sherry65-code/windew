#include <windew/windew.hpp>

#ifdef _WIN64

WNDCLASSEX wc;
HWND hwnd;
MSG Msg;

const char g_szClassName[] = "windew";

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void setDarkMode(HWND hwnd, bool enabled) {
    if (enabled) {
        BOOL value = TRUE;
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));
    }
}

// Init Function for Window
Windew::Windew(Wininfo_t& wininfo) {
    hInstance = GetModuleHandle(nullptr); // Retrieve Instance handle

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(2);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Failed to Register!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        wininfo.title.c_str(),
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        wininfo.x, 
        wininfo.y, 
        NULL, 
        NULL, 
        hInstance, 
        NULL
    );

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    if (wininfo.darkmode)
        setDarkMode(hwnd, true);

    ShowWindow(hwnd, SW_SHOW);

    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
}

Windew::~Windew() {
    UnregisterClass(g_szClassName, hInstance);
}

#endif