
/*
 *   Source File [keyboard.cpp]
 */

#include "Violet.h"

namespace Vi {
	
	bool Keyboard::pressing(int button) {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		}

		if (button >= SDL_SCANCODE_COUNT) {
			Log::error(HERE);
			std::terminate();
		}

		return curr_keys[button];
	}

	bool Keyboard::pressed(int button) {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		}

		if (button >= SDL_SCANCODE_COUNT) {
			Log::error(HERE);
			std::terminate();
		}

		return (!prev_keys[button]) && (curr_keys[button]);
	}

	bool Keyboard::released(int button) {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		}

		if (button >= SDL_SCANCODE_COUNT) {
			Log::error(HERE);
			std::terminate();
		}

		return (prev_keys[button]) && (!curr_keys[button]);
	}
}

