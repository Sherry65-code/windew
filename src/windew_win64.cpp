#pragma once
#ifdef _WIN64
#include "windew/windew.hpp"

const char g_szClassName[] = "windew";
HWND hwnd;
MSG Msg;

std::vector<Windew::button> buttons;
std::vector<HWND> buttonHandles;
std::vector<Windew::label> labels;
std::vector<HWND> labelHandles;
std::vector<Windew::textbox> textboxes;
std::vector<HWND> textboxHandles;

HFONT Windew::setFont(font& font) {
    HFONT hFont = CreateFont(
        -font.size,       // Height of the font (negative for character height)
        0,              // Average character width
        0,              // Angle of escapement
        0,              // Base-line orientation angle
        FW_REGULAR,     // Font weight
        FALSE,          // Italic
        FALSE,          // Underline
        FALSE,          // Strikeout
        DEFAULT_CHARSET, // Character set
        OUT_OUTLINE_PRECIS, // Output precision
        CLIP_DEFAULT_PRECIS, // Clipping precision
        CLEARTYPE_QUALITY, // Font quality
        DEFAULT_PITCH | FF_DONTCARE, // Pitch and family
        font.name.c_str()); // Font name

    if (!hFont) {
        // Handle font creation error (e.g., log a message)
        OutputDebugStringA("Font creation failed!\n"); // Or use MessageBox
        return nullptr;
    }

    return hFont;
}

void Windew::createButton(button& constructor) {
    buttons.push_back(constructor);
    if (hwnd == NULL) return;
    HWND h = CreateWindowW(L"BUTTON", std::wstring(constructor.text.begin(), constructor.text.end()).c_str(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        constructor.x, constructor.y, constructor.w, constructor.h, hwnd,
        (HMENU)buttons.size(), GetModuleHandle(NULL), NULL);
    
	buttonHandles.push_back(h);

	HFONT buttonFont = setFont(constructor.userfont);
    SendMessage(h, WM_SETFONT, (WPARAM)buttonFont, TRUE);
}

void Windew::createLabel(label& constructor) {
    labels.push_back(constructor);    
    if (hwnd == NULL) return;
    HWND h = CreateWindowW(L"STATIC", std::wstring(constructor.text.begin(), constructor.text.end()).c_str(),
        WS_VISIBLE | WS_CHILD | SS_LEFT,
        constructor.x, constructor.y, constructor.w, constructor.h, hwnd,
        NULL, GetModuleHandle(NULL), NULL);

	labelHandles.push_back(h);

	HFONT labelFont = setFont(constructor.userfont);
	SendMessage(h, WM_SETFONT, (WPARAM)labelFont, TRUE);
}

void Windew::createTextbox(textbox& constructor) {
	textboxes.push_back(constructor);
    if (hwnd == NULL) return;
	HWND h = CreateWindowW(L"EDIT", L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		constructor.x, constructor.y, constructor.w, constructor.h, hwnd,
		NULL, GetModuleHandle(NULL), NULL);

	textboxHandles.push_back(h);

	HFONT textboxFont = setFont(constructor.userfont);
	SendMessage(h, WM_SETFONT, (WPARAM)textboxFont, TRUE);
}

void Windew::popup(std::string& title, std::string& message) {
	MessageBoxA(hwnd, message.c_str(), title.c_str(), MB_OK);
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED) {
            int buttonId = LOWORD(wParam); // Get the button ID
            for (int i = 0; i < buttons.size(); i++) {
                if ((HMENU)(1-i) == (HMENU)buttonId) {
                    if (buttons[i].callback) {
                        buttons[i].callback(); // Invoke the callback
                    }
                    break;
                }
            }
        }
        break;
    case WM_CREATE:
        break;
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

// Initializer
Windew::Windew(std::string& title, uint32_t w, uint32_t h, bool resizable, bool fullscreen) {
    WNDCLASSEX wc;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOWDEFAULT;

    // Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, w, h,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
}

// Main loop function
void Windew::update() {
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
}

bool Windew::shouldClose() {
    return !(GetMessage(&Msg, NULL, 0, 0) > 0);
}

// Cleanup Code
Windew::~Windew() {
    if (hwnd != NULL) {
        DestroyWindow(hwnd);
        hwnd = NULL;
    }
    UnregisterClass(g_szClassName, GetModuleHandle(NULL));
}

#endif
