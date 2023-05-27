#include "shader.h"

#include <glad/gl.h>

#include <filesystem>
#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(std::string_view vs, std::string_view fs) {
    std::ifstream file;

    if (!std::filesystem::exists(vs)) {
        std::cerr << "Vertex shader file does not exist!" << std::endl;
        return;
    }

    if (!std::filesystem::exists(fs)) {
        std::cerr << "Fragment shader file does not exist!" << std::endl;
        return;
    }

    file.open(vs);
    std::string vertexShaderData;

    file.seekg(0, std::ios::end);
    vertexShaderData.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    vertexShaderData.assign((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    file.close();

    file.open(fs);
    std::string fragmentShaderData;

    file.seekg(0, std::ios::end);
    fragmentShaderData.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    fragmentShaderData.assign((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
    file.close();

    create_program(vertexShaderData, fragmentShaderData);
}

void ShaderProgram::create_program(std::string_view vs, std::string_view fs) {
    _id = glCreateProgram();
    _vertexShader = compile_shader(vs, ShaderType::Vertex);
    _fragmentShader = compile_shader(fs, ShaderType::Fragment);

    glAttachShader(_id, _vertexShader);
    glAttachShader(_id, _fragmentShader);
    glLinkProgram(_id);

    check_errors(_id, ShaderType::Unknown);
}

uint32_t ShaderProgram::compile_shader(std::string_view source, ShaderType type) const {
    auto shaderType = 0;
    switch (type) {
        case Vertex:
            shaderType = GL_VERTEX_SHADER;
            break;
        case Fragment:
            shaderType = GL_FRAGMENT_SHADER;
            break;
        default:
            std::cerr << "Unknown shader type!" << std::endl;
            return 0;
    }

    auto vertexShader = glCreateShader(shaderType);

    const char *src = source.data();
    glShaderSource(vertexShader, 1, &src, nullptr);
    glCompileShader(vertexShader);

    check_errors(vertexShader, ShaderType::Vertex);
    return vertexShader;
}

void ShaderProgram::use() const {
    glUseProgram(_id);
}

void ShaderProgram::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int) value);
}

void ShaderProgram::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void ShaderProgram::check_errors(uint32_t object, ShaderType type) const {
    constexpr int error_string_size = 512;
    int success = 0;
    char infoLog[error_string_size];
    switch (type) {
        case Vertex:
        case Fragment:
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(object, error_string_size, nullptr, infoLog);
                std::cerr << "Shader: Program compilation failed\n"
                          << infoLog << std::endl;
            }
            break;
        default:
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(object, error_string_size, nullptr, infoLog);
                std::cerr << "Shader: Shader compilation failed\n"
                          << infoLog << std::endl;
            }
            break;
    }
}

uint32_t ShaderProgram::id() const {
    return _id;
}

ShaderProgram::~ShaderProgram() {
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);
    glDeleteProgram(_id);
}
