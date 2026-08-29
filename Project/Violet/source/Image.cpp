
/*
 *   Source File [Image.cpp]
 */

#include "Violet.h"
#include "stb_image.h"

namespace Vi {
	
	// Constructors

	Image::Image(std::filesystem::path path) {
		int width, height, n;
		std::string path_string = path.string();
		const char* path_cstring = path_string.c_str();
		stbi_set_flip_vertically_on_load(true);
		uint8_t* stbi_image = stbi_load(path_cstring, &width, &height, &n, 4);
		dimensions = { static_cast<size_t>(width), static_cast<size_t>(height) };
		size_t buffer_size = (dimensions.x * dimensions.y * (size_t)4);
		pixels = new uint8_t[buffer_size];
		if (!pixels) { throw std::exception{}; }
		std::memcpy(pixels, stbi_image, buffer_size);
		stbi_image_free(stbi_image);
	}

	Image::Image(Vec2u size) {
		size_t buffer_size = (size.x * size.y * (size_t)4);
		pixels = new uint8_t[buffer_size];
		if (!pixels) { throw std::exception{}; }
		std::memset(pixels, (uint8_t)255, buffer_size);
		dimensions = size;
	}

	Image Image::perlin(Vec2u size, size_t num_layers, double dropoff) {
		return {}; // todo: impl!
	}

	Image::~Image() {
		delete[] pixels;
		dimensions = {};
	}

	// Copy & Move Semantics

	Image::Image(const Image& other) {
		const size_t buffer_size = (other.dimensions.x * other.dimensions.y * (size_t)4);
		pixels = new uint8_t[buffer_size];
		if (!pixels) { throw std::exception{}; }
		std::memcpy(pixels, other.pixels, buffer_size);
		dimensions = other.dimensions;
	}

	Image::Image(Image&& other) noexcept {
		pixels = other.pixels;
		dimensions = other.dimensions;
		other.pixels = nullptr;
		other.dimensions = {};
	}

	Image& Image::operator = (const Image& other) {
		if (this == std::addressof(other)) { throw std::exception{}; }
		const size_t buffer_size = (other.dimensions.x * other.dimensions.y * (size_t)4);
		delete[] pixels;
		pixels = new uint8_t[buffer_size];
		if (!pixels) { throw std::exception{}; }
		std::memcpy(pixels, other.pixels, buffer_size);
		dimensions = other.dimensions;
		return *this;
	}

	Image& Image::operator = (Image&& other) noexcept {
		if (this == std::addressof(other)) { std::terminate(); }
		delete[] pixels;
		pixels = other.pixels;
		dimensions = other.dimensions;
		other.pixels = nullptr;
		other.dimensions = {};
		return *this;
	}

	// API Interface

	void Image::putPixel(Vec2u position, Color color) {
		if (!pixels) { throw std::exception{}; }
		if (position.x >= dimensions.x) { throw std::exception{}; }
		if (position.y >= dimensions.y) { throw std::exception{}; }
		uint8_t r = static_cast<uint8_t>(color.r * 255.0f);
		uint8_t g = static_cast<uint8_t>(color.g * 255.0f);
		uint8_t b = static_cast<uint8_t>(color.b * 255.0f);
		uint8_t a = static_cast<uint8_t>(color.a * 255.0f);
		size_t index = (((position.y * dimensions.x) + position.x) * (size_t)4);
		pixels[index + 0] = r;
		pixels[index + 1] = g;
		pixels[index + 2] = b;
		pixels[index + 3] = a;
	}

	Color Image::getPixel(Vec2u position) const {
		if (!pixels) { throw std::exception{}; }
		if (position.x >= dimensions.x) { throw std::exception{}; }
		if (position.y >= dimensions.y) { throw std::exception{}; }
		size_t index = (((position.y * dimensions.x) + position.x) * (size_t)4);
		uint8_t r = pixels[index + 0];
		uint8_t g = pixels[index + 1];
		uint8_t b = pixels[index + 2];
		uint8_t a = pixels[index + 3];
		return {
			static_cast<float>(r) / 255.0f,
			static_cast<float>(g) / 255.0f,
			static_cast<float>(b) / 255.0f,
			static_cast<float>(a) / 255.0f,
		};
	}

	const uint8_t* Image::ptr(size_t& buffer_size) const {
		buffer_size = (dimensions.x * dimensions.y * (size_t)4);
		return pixels;
	}

	Vec2u Image::size() const {
		return dimensions;
	}
}

