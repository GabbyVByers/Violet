
/*******************/
/*   texture.cpp   */
/*******************/

#include "rendering.h"
#include <cassert>

namespace Vi {
	
	/* Public */

	Texture::Texture(const Image& i) {
		image = i;
		generate();
	}

	Texture::Texture(const Texture& other) {
		image = other.image;
		generate();
	}

	Texture::Texture(Texture&& other) noexcept {
		image = std::move(other.image);
		glTextureID = std::move(other.glTextureID);
		other.glTextureID = 0;
	}

	Texture& Texture::operator = (const Texture& other) {
		if (this == &other)
			return *this;
		destroy();
		image = other.image;
		generate();
		return *this;
	}

	Texture& Texture::operator = (Texture&& other) noexcept {
		if (this == &other)
			return *this;
		destroy();
		image = std::move(other.image);
		glTextureID = std::move(other.glTextureID);
		other.glTextureID = 0;
		return *this;
	}

	Texture::~Texture() {
		destroy();
	}

	/* Private */

	void Texture::generate() {
		assert(glTextureID == 0);
		int width = (int)image.width();
		int height = (int)image.height();
		unsigned char* data = image.pixels.get();
		glGenTextures(1, &glTextureID);
		glBindTexture(GL_TEXTURE_2D, glTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void Texture::destroy() {
		if (glTextureID == 0) return;
		glDeleteTextures(1, &glTextureID);
		glTextureID = 0;
	}
}

