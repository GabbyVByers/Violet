
/*
    texture.cpp
*/

#include "../rendering.h"
#include "../logging.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <utility>

namespace Vi {
    
    Texture::Texture(const std::string& path) {
        this->path = path;
        if (path == "") {
            unsigned char white[] = { 255, 255, 255, 255 };
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
            return;
        }

        int width, height;
        int num_color_channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &num_color_channels, NULL);
        if (data == NULL) {
            Log::error("Failed to load image: ", path);
        }

        GLenum format = NULL;
        if (num_color_channels == 1) format = GL_RED;
        if (num_color_channels == 3) format = GL_RGB;
        if (num_color_channels == 4) format = GL_RGBA;
        if (format == NULL) {
            Log::error("Could not parse image format");
        }

        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    Texture::Texture(const Texture& other) : Texture(other.path) {}

    Texture::Texture(Texture&& other) noexcept {
        path = std::move(other.path);
        texture_id = other.texture_id;
        other.path = "";
        other.texture_id = NULL;
    }

    Texture& Texture::operator = (const Texture& other) {
        if (this == &other)
            return *this;
        destroy_texture();
        Texture temp(other.path);
        std::swap(temp.path, path);
        std::swap(temp.texture_id, texture_id);
        return *this;
    }

    Texture& Texture::operator = (Texture&& other) noexcept {
        if (this == &other)
            return *this;
        destroy_texture();
        path = std::move(other.path);
        texture_id = other.texture_id;
        other.path = "";
        other.texture_id = NULL;
        return *this;
    }

    Texture::~Texture() {
        destroy_texture();
    }

    void Texture::destroy_texture() noexcept {
        if (path != "") {
            path = "";
        }
        if (texture_id != NULL) {
            glDeleteTextures(1, &texture_id);
            texture_id = NULL;
        }
    }
}

