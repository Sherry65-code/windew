#include <windew/windew.hpp>

void static login_pressed() {
	std::string title = "Login";
	std::string message = "Login button pressed!";
	Windew::popup(title, message);
}

int main() {
	std::string title = "Eclipse Login";
	Windew windew(title, 400, 350, true, false);
	
	windew.createLabel(Windew::label{ "Login", 50, 50, 120, 65, Windew::font{"Segoe UI", 45} });
	windew.createLabel(Windew::label{ "Username", 50, 150, 70, 20, Windew::font{"Segoe UI", 15} });
	windew.createTextbox(Windew::textbox{ 140, 150, 200, 20, Windew::font{"Segoe UI", 15} });
	windew.createLabel(Windew::label{ "Password", 50, 180, 70, 20, Windew::font{"Segoe UI", 15} });
	windew.createTextbox(Windew::textbox{ 140, 180, 200, 20, Windew::font{"Segoe UI", 15} });
	windew.createButton(Windew::button{ "Continue", 50, 220, 90, 30, Windew::font{"Segoe UI", 15}, login_pressed});

	while (!windew.shouldClose()) {
		windew.update();
	}
}