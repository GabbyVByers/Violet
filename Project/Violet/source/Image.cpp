
/*
 *   Source File [image.cpp]
 */

#include "Violet.h"
#include "stb_image.h"
#include <cstdint>

// STB Image Wrapper

static struct STB_LoadPNGResult {
	uint8_t* pixels;
	size_t buffer_size;
	size_t width;
	size_t height;
};

[[nodiscard]] static bool STB_LoadPNG(STB_LoadPNGResult& result, const std::filesystem::path& path) {
	result = STB_LoadPNGResult {
		.pixels = nullptr,
		.buffer_size = 0,
		.width = 0,
		.height = 0,
	};

	std::string path_string = path.string();
	const char* path_cstr = path_string.c_str();

	int w, h, n;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(path_cstr, &w, &h, &n, 4);
	if (!pixels) { return false; }
	size_t width = static_cast<size_t>(w);
	size_t height = static_cast<size_t>(h);

	result = STB_LoadPNGResult{
		.pixels = pixels,
		.buffer_size = (width * height * (size_t)4),
		.width = width,
		.height = height,
	}; return true;
}

[[nodiscard]] static bool STB_FreePNG(unsigned char* pixels) {
	if (!pixels) { return false; }
	stbi_image_free(pixels);
	return true;
}

namespace Vi {
	
	// Constructors

	Image::Image(Vec2u dimensions) {
		size_t buffer_size = (dimensions.x * dimensions.y * (size_t)4);
		this->dimensions = dimensions;
		pixels = new uint8_t[buffer_size];
		if (!pixels) {
			Log::error(HERE);
			std::terminate();
		} std::memset(pixels, (uint8_t)255, buffer_size);
	}

	Image::Image(std::filesystem::path path) {
		STB_LoadPNGResult result{};
		if (!STB_LoadPNG(result, path)) {
			Log::error(HERE);
			std::terminate();
		}

		pixels = new uint8_t[result.buffer_size];
		if (!pixels) {
			Log::error(HERE);
			std::terminate();
		} std::memcpy(pixels, result.pixels, result.buffer_size);

		dimensions = Vec2u {
			.x = result.width,
			.y = result.height,
		};

		if (!STB_FreePNG(result.pixels)) {
			Log::error(HERE);
			std::terminate();
		}
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
		const size_t buffer_size = (other.dimensions.x * other.dimensions.y * (size_t)4);
		dimensions = other.dimensions;
		pixels = new uint8_t[buffer_size];
		if (!pixels) {
			Log::error(HERE);
			std::terminate();
		} std::memcpy(pixels, other.pixels, buffer_size);
	}

	Image::Image(Image&& other) noexcept {
		pixels = other.pixels;
		dimensions = other.dimensions;
		other.pixels = nullptr;
		other.dimensions = {};
	}

	Image& Image::operator = (const Image& other) {
		if (this == std::addressof(other)) {
			Log::error(HERE);
			std::terminate();
		} const size_t buffer_size = (other.dimensions.x * other.dimensions.y * (size_t)4);
		dimensions = other.dimensions;
		delete[] pixels;
		pixels = new uint8_t[buffer_size];
		if (!pixels) {
			Log::error(HERE);
			std::terminate();
		} std::memcpy(pixels, other.pixels, buffer_size);
		return *this;
	}

	Image& Image::operator = (Image&& other) noexcept {
		if (this == std::addressof(other)) {
			Log::error(HERE);
			std::terminate();
		} delete[] pixels;
		pixels = other.pixels;
		dimensions = other.dimensions;
		other.pixels = nullptr;
		other.dimensions = {};
		return *this;
	}

	// API Interface

	void Image::putPixel(Vec2u position, Color color) {
		if (!pixels) {
			Log::error(HERE);
			std::terminate();
		} if ((position.x >= dimensions.x) || (position.y >= dimensions.y)) {
			Log::error(HERE);
			std::terminate();
		} uint8_t r = static_cast<uint8_t>(color.r * 255.0f);
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
		if (!pixels) {
			Log::error(HERE);
			std::terminate();
		} if ((position.x >= dimensions.x) || (position.y >= dimensions.y)) {
			Log::error(HERE);
			std::terminate();
		} size_t index = (((position.y * dimensions.x) + position.x) * (size_t)4);
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

