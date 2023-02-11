#include "shader.h"

#include <glad/gl.h>
#include <iostream>

Shader::Shader(const char *vs, const char *fs) {
    create_program(vs, fs);
}

void Shader::create_program(const char *vs,const char *fs)
{
    _id = glCreateProgram();
    uint32_t vertexShader = compile_shader(vs, ShaderType::Vertex);
    uint32_t fragmentShader = compile_shader(fs, ShaderType::Fragment);

    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);

    check_compile_errors(_id, ShaderType::Program);
}

uint32_t Shader::compile_shader(const char *source, ShaderType type) const
{
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
    glShaderSource(vertexShader, 1, &source, nullptr);
    glCompileShader(vertexShader);

    check_compile_errors(vertexShader, ShaderType::Vertex);
    return vertexShader;
}

void Shader::use() const
{
    glUseProgram(_id);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

void  Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::check_compile_errors(uint32_t object, ShaderType type) const {
    constexpr int error_string_size = 512;
    int success = 0;
    char infoLog[error_string_size];
    switch (type) {
        case Vertex:
        case Fragment:
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(object, error_string_size, nullptr, infoLog);
                std::cerr << "Shader: Program compilation failed\n" << infoLog << std::endl;
            }
            break;
        default:
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(object, error_string_size, nullptr, infoLog);
                std::cerr << "Shader: Shader compilation failed\n" << infoLog << std::endl;
            }
            break;
    }
}

uint32_t Shader::id() const {
    return _id;
}

Shader::~Shader() {
}
