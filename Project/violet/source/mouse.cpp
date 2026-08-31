
/*
 *   Source File [mouse.cpp]
 */

#include "Violet.h"

namespace Vi {
	
	void Mouse::hide() {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		}

		saved_position = pos;
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

		pos = saved_position;
		SDL_WarpMouseInWindow(Window::window, pos.x, pos.y);
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

	Vec2f Mouse::position() {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		} return pos;
	}

	Vec2f Mouse::velocity() {
		if (!Window::created) {
			Log::error(HERE);
			std::terminate();
		} return vel;
	}
}

