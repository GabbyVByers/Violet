
/*
    material.cpp
*/

#include "../rendering.h"
#include "../logging.h"
#include <fstream>
#include <sstream>
#include <utility>

namespace Vi {

    Material::Material(const std::string& path, const GLenum primitive) {
        this->path = path;
        this->primitive = primitive;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(2);

        auto load = [](std::string path) -> std::string {
            std::ifstream file(path);
            if (!file) {
                Log::error("Could not load file: ", path);
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        };

        std::string root = __FILE__;
        std::string vert_source = load(root + "../../Shaders/" + path + ".vert");
        std::string frag_source = load(root + "../../Shaders/" + path + ".frag");
        const char* vert_c_str = vert_source.c_str();
        const char* frag_c_str = frag_source.c_str();

        GLuint vert_program = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert_program, 1, &vert_c_str, nullptr);
        glCompileShader(vert_program);
        GLint success;
        glGetShaderiv(vert_program, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            Log::error("Failed to compile vertex shader");
        }

        GLuint frag_program = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag_program, 1, &frag_c_str, nullptr);
        glCompileShader(frag_program);
        glGetShaderiv(frag_program, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            Log::error("Failed to compile fragment shader");
        }

        shader_program = glCreateProgram();
        glAttachShader(shader_program, vert_program);
        glAttachShader(shader_program, frag_program);
        glLinkProgram(shader_program);
        glDeleteShader(vert_program);
        glDeleteShader(frag_program);
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {
            Log::error("Failed to link shader program");
        }
    }

    Material::Material(const Material& other) : Material(other.path, other.primitive) {}

    Material::Material(Material&& other) noexcept {
        path = std::move(other.path);
        primitive = other.primitive;
        shader_program = other.shader_program;
        vao = other.vao;
        vbo = other.vbo;
        other.path = "";
        other.primitive = NULL;
        other.shader_program = NULL;
        other.vao = NULL;
        other.vbo = NULL;
    }

    Material& Material::operator = (const Material& other) {
        if (this == &other)
            return *this;
        destroy_material();
        Material temp(other.path, other.primitive);
        std::swap(temp.path, path);
        std::swap(temp.primitive, primitive);
        std::swap(temp.shader_program, shader_program);
        std::swap(temp.vao, vao);
        std::swap(temp.vbo, vbo);
        return *this;
    }

    Material& Material::operator = (Material&& other) noexcept {
        if (this == &other)
            return *this;
        destroy_material();
        path = std::move(other.path);
        primitive = other.primitive;
        shader_program = other.shader_program;
        vao = other.vao;
        vbo = other.vbo;
        other.path = "";
        other.primitive = NULL;
        other.shader_program = NULL;
        other.vao = NULL;
        other.vbo = NULL;
        return *this;
    }

    Material::~Material() {
        destroy_material();
    }

    void Material::destroy_material() noexcept {
        path = "";
        primitive = NULL;
        if (shader_program != NULL) {
            glDeleteProgram(shader_program);
            shader_program = NULL;
        }
        if (vao != NULL) {
            glDeleteVertexArrays(1, &vao);
            vao = NULL;
        }
        if (vbo != NULL) {
            glDeleteBuffers(1, &vbo);
            vbo = NULL;
        }
    }
}

