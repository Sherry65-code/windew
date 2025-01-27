#pragma once

#include <string>
#include <vector>
#include <functional>

#ifdef _WIN64
#include <Windows.h>
#elif __unix__
#endif

class Windew {
public:
	struct font {
		std::string name;
		uint32_t size;
	};

	struct button {
		std::string text;
		uint32_t x;
		uint32_t y;
		uint32_t w;
		uint32_t h;
		font& userfont;
		std::function<void()> callback;
	};
	struct label {
		std::string text;
		uint32_t x;
		uint32_t y;
		uint32_t w;
		uint32_t h;
		font& userfont;
	};
	struct textbox {
		uint32_t x;
		uint32_t y;
		uint32_t w;
		uint32_t h;
		font& userfont;
	};

	Windew(std::string& title, uint32_t w, uint32_t h, bool resizable, bool fullscreen);
	void update();
	bool shouldClose();
	~Windew();

	void createButton(button& constructor);
	void createLabel(label& constructor);
	void createTextbox(textbox& constructor);

	static void popup(std::string& title, std::string& message);

private:
#ifdef _WIN64
	HFONT setFont(font& font);
#endif
};