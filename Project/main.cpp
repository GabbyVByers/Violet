
/*
 *   Source File [main.cpp]
 */

#include "Violet.h"
#include <iostream>

int main() {
	Vi::Window window{ "App Title", 500, 500 };

	while (window.isOpen()) {
		window.clear({1,0,1,1});
		window.display();
	}

	return 0;
}

