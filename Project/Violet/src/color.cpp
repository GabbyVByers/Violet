
/*****************/
/*   color.cpp   */
/*****************/

#include "rendering.h"

namespace Vi {

	/* Public */

	Color Color::white() {
		return Color{ 1.0f, 1.0f, 1.0f, 1.0f };
	}

	Color Color::black() {
		return Color{ 0.0f, 0.0f, 0.0f, 1.0f };
	}

	Color Color::red() {
		return Color{ 1.0f, 0.0f, 0.0f, 1.0f };
	}

	Color Color::green() {
		return Color{ 0.0f, 1.0f, 0.0f, 1.0f };
	}

	Color Color::blue() {
		return Color{ 0.0f, 0.0f, 1.0f, 1.0f };
	}
}

