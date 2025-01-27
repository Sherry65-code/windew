#include "windew/windew.hpp"
#include <string>

int main() {
	std::string title = "Hello, World!";
	Windew window(title, 800, 600, true, false);
}