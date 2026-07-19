
/* image.cpp */

#include "rendering.h"

namespace Vi {

	Image::Image(const Vec2i<int>& size) {
		this->size = size;
		size_t buffer_size = (size_t)size.x * (size_t)size.y * 4;
		pixels = std::make_unique<unsigned char[]>(buffer_size);
		for (size_t i{}; i < 4; i++) {
			pixels[i] = 255u;
		}
	}

	Image::Image(const char* path) {
		int w{}, h{}, n{};
		stbi_set_flip_vertically_on_load(true);
		unsigned char* stbi_image = stbi_load(path, &w, &h, &n, 4);
		size.x = w; size.y = h;
		size_t buffer_size = (size_t)w * (size_t)h * 4;
		pixels = std::make_unique<unsigned char[]>(buffer_size);
		for (size_t i{}; i < buffer_size; i++) {
			pixels[i] = stbi_image[i];
		} free(stbi_image);
	}

	int Image::width() const {
		return size.x;
	}

	int Image::height() const {
		return size.y;
	}

	Color Image::getPixel(const Vec2i<int>& position) const {
		assert(position.x < size.x);
		assert(position.y < size.y);
		return Color{};
	}

	void Image::setPixel(const Vec2i<int>& position, const Color& color) {
		assert(position.x < size.x);
		assert(position.y < size.y);
	}
}

