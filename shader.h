#ifndef LEARN_SHADER_H
#define LEARN_SHADER_H

#include <cstdint>
#include <string>

enum ShaderType {
    Unknown,
    Vertex,
    Fragment
};

class Shader {
public:
    Shader(const char* vs, const char* fs);
    ~Shader();

    void use() const;
    [[nodiscard]] uint32_t id() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    void create_program(const char* vs, const char* fs);
    uint32_t compile_shader(const char* source, ShaderType type) const;
    void check_compile_errors(uint32_t object, ShaderType type) const;

    uint32_t _id{};
    uint32_t _vertexShader{};
    uint32_t _fragmentShader{};
};


#endif//LEARN_SHADER_H
