
/* image.cpp */

#include "rendering.h"
#include "stb/stb_image.h"

namespace Vi {

	/* Public */

	Image::Image(const Vec2i<size_t>& size) {
		assert((size.x != 0) && (size.y != 0));
		this->size = size;
		size_t buffer_size = size.x * size.y * 4;
		pixels = std::make_shared<unsigned char[]>(buffer_size);
		for (size_t i{}; i < buffer_size; i++) {
			pixels[i] = 255u;
		}
	}

	Image::Image(const char* path) {
		int w{}, h{}, n{};
		stbi_set_flip_vertically_on_load(true);
		unsigned char* stbi_image = stbi_load(path, &w, &h, &n, 4);
		assert(stbi_image != nullptr);
		size.x = w; size.y = h;
		size_t buffer_size = (size_t)w * (size_t)h * 4;
		pixels = std::make_shared<unsigned char[]>(buffer_size);
		for (size_t i{}; i < buffer_size; i++) {
			pixels[i] = stbi_image[i];
		} stbi_image_free(stbi_image);
	}

	size_t Image::width() const {
		return size.x;
	}

	size_t Image::height() const {
		return size.y;
	}

	Color Image::getPixel(const Vec2i<size_t>& position) const {
		assert(position.x < size.x);
		assert(position.y < size.y);
		size_t index = ((position.y * size.x) + position.x) * 4;
		unsigned char r = pixels[index + 0];
		unsigned char g = pixels[index + 1];
		unsigned char b = pixels[index + 2];
		unsigned char a = pixels[index + 3];
		return Color{
			(float)r / 255.f,
			(float)g / 255.f,
			(float)b / 255.f,
			(float)a / 255.f
		};
	}

	void Image::setPixel(const Vec2i<size_t>& position, const Color& color) {
		assert(position.x < size.x);
		assert(position.y < size.y);
		size_t index = ((position.y * size.x) + position.x) * 4;
		pixels[index + 0] = (unsigned char)(color.r * 255.f);
		pixels[index + 1] = (unsigned char)(color.g * 255.f);
		pixels[index + 2] = (unsigned char)(color.b * 255.f);
		pixels[index + 3] = (unsigned char)(color.a * 255.f);
	}
}

