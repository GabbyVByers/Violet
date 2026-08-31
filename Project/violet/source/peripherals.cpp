
/*
 *   Source File [peripherals.cpp]
 */

#include "Violet.h"

namespace Vi {
	
	// MOUSE

	void Mouse::hide() {
		if (!Window::created) { throw std::exception{}; }
		saved_position = pos;
		SDL_SetWindowRelativeMouseMode(Window::window, true);
	}
	
	void Mouse::reveal() {
		if (!Window::created) { throw std::exception{}; }
		pos = saved_position;
		SDL_WarpMouseInWindow(Window::window, pos.x, pos.y);
		SDL_SetWindowRelativeMouseMode(Window::window, false);
	}
	
	bool Mouse::pressing(int button) {
		if (!Window::created) { throw std::exception{}; }
		return (curr_state & SDL_BUTTON_MASK(button)) != 0;
	}

	bool Mouse::pressed(int button) {
		if (!Window::created) { throw std::exception{}; }
		return ((prev_state & SDL_BUTTON_MASK(button)) == 0) && ((curr_state & SDL_BUTTON_MASK(button)) != 0);
	}

	bool Mouse::released(int button) {
		if (!Window::created) { throw std::exception{}; }
		return ((prev_state & SDL_BUTTON_MASK(button)) != 0) && ((curr_state & SDL_BUTTON_MASK(button)) == 0);
	}

	Vec2f Mouse::position() {
		if (!Window::created) { throw std::exception{}; }
		return pos;
	}

	Vec2f Mouse::velocity() {
		if (!Window::created) { throw std::exception{}; }
		return vel;
	}

	// KEYBOARD

	bool Keyboard::pressing(int button) {
		if (!Window::created) { throw std::exception{}; }
		if (button >= SDL_SCANCODE_COUNT) { throw std::exception{}; }
		return curr_keys[button];
	}

	bool Keyboard::pressed(int button) {
		if (!Window::created) { throw std::exception{}; }
		if (button >= SDL_SCANCODE_COUNT) { throw std::exception{}; }
		return (!prev_keys[button]) && (curr_keys[button]);
	}

	bool Keyboard::released(int button) {
		if (!Window::created) { throw std::exception{}; }
		if (button >= SDL_SCANCODE_COUNT) { throw std::exception{}; }
		return (prev_keys[button]) && (!curr_keys[button]);
	}
}

