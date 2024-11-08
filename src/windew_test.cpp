#include <windew/windew.hpp>

int main() {
	Windew::WinInfo_t wininfo;
	wininfo.title = "Hello, Windew!";
	wininfo.x = 1000;
	wininfo.y = 400;
	wininfo.resizable = false;
	wininfo.fullscreen = false;
	wininfo.darkmode = true;

	Windew windew(wininfo);
}