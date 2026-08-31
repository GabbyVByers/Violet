
/*
 *   Source File [image.cpp]
 */

#include "Violet.h"
#include "stb_image.h"
#include <cstdint>

namespace Vi {
	
	// Constructors

	Image::Image(Vec2u dimensions) {
		size_t buffer_size = (dimensions.x * dimensions.y * (size_t)4);
		if (buffer_size == 0) {
			pixels = nullptr;
			this->dimensions = {};
			return;
		}

		this->dimensions = dimensions;
		pixels = new uint8_t[buffer_size];
		std::memset(pixels, (uint8_t)255, buffer_size);
	}

	Image::Image(std::filesystem::path path) {
		std::string path_string = path.string();
		const char* path_cstr = path_string.c_str();

		int w, h, n;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* stbi_image = stbi_load(path_cstr, &w, &h, &n, 4);
		if (!stbi_image) { std::cout << std::format("Couldn't Open: {}\n", path.string()); std::terminate(); }

		size_t width = static_cast<size_t>(w);
		size_t height = static_cast<size_t>(h);
		size_t buffer_size = (width * height * (size_t)4);

		pixels = new uint8_t[buffer_size];
		std::memcpy(pixels, stbi_image, buffer_size);
		dimensions = { width, height, };
		stbi_image_free(stbi_image);
	}

	Image::Image(Vec2u dimesnsions, size_t layers, double attenuation) {
		// todo: impl!
	}

	Image::~Image() {
		delete[] pixels;
		dimensions = {};
	}

	// Copy & Move Semantics

	Image::Image(const Image& other) {
		dimensions = other.dimensions;
		pixels = nullptr;
		size_t buffer_size = dimensions.x * dimensions.y * 4;
		if (buffer_size != 0) {
			pixels = new uint8_t[buffer_size];
			std::memcpy(pixels, other.pixels, buffer_size);
		}
	}

	Image::Image(Image&& other) noexcept {
		pixels = other.pixels;
		dimensions = other.dimensions;
		other.pixels = nullptr;
		other.dimensions = {};
	}

	Image& Image::operator=(const Image& other) {
		if (this == &other) { return *this; }
		dimensions = other.dimensions;
		delete[] pixels;
		pixels = nullptr;
		const size_t buffer_size = dimensions.x * dimensions.y * 4;
		if (buffer_size != 0) {
			pixels = new uint8_t[buffer_size];
			std::memcpy(pixels, other.pixels, buffer_size);
		} return *this;
	}

	Image& Image::operator=(Image&& other) noexcept {
		if (this == &other) { return *this; }
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

	const uint8_t* Image::ptr() const {
		return pixels;
	}

	Vec2u Image::size() const {
		return dimensions;
	}
}

