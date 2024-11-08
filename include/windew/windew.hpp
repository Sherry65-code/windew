#include <string>

#ifdef _WIN64
#include <windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#endif

#ifdef unix
#include <x11/x.h>
#endif

class Windew {
public:
	// Window Creation Structure
	typedef struct WinInfo_t {
		std::string title;	// Window Title
		size_t x;			// Window X Coord Size
		size_t y;			// Window Y Coord Size
		bool resizable;		// Can window be resized
		bool fullscreen;	// Is window fullscreen (X and Y coords will be treated as resolution)
		bool darkmode;		// Sets dark mode for window titlebar
	} Wininfo_t;

	Windew(WinInfo_t& wininfo);
	~Windew();

private:
	HINSTANCE hInstance;
};