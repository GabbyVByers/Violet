
/*
 *   Source File [mouse.cpp]
 */

#include "Violet.h"

namespace Vi {
	
	// PUBLIC

	void Mouse::hide() {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		}

		saved_position = position;
		if (!SDL_SetWindowRelativeMouseMode(Window::window, true)) {
			Log::error(SDL_GetError());
			std::terminate();
		}
	}
	
	void Mouse::reveal() {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		}

		position = saved_position;
		SDL_WarpMouseInWindow(Window::window, position.x, position.y);
		if (!SDL_SetWindowRelativeMouseMode(Window::window, false)) {
			Log::error(SDL_GetError());
			std::terminate();
		}
	}
	
	bool Mouse::pressing(int button) {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		} return (curr_state & SDL_BUTTON_MASK(button)) != 0;
	}

	bool Mouse::pressed(int button) {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		} return ((prev_state & SDL_BUTTON_MASK(button)) == 0) && ((curr_state & SDL_BUTTON_MASK(button)) != 0);
	}

	bool Mouse::released(int button) {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		} return ((prev_state & SDL_BUTTON_MASK(button)) != 0) && ((curr_state & SDL_BUTTON_MASK(button)) == 0);
	}
}

