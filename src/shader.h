#ifndef LEARN_SHADER_H
#define LEARN_SHADER_H

#include <cstdint>
#include <string_view>

enum ShaderType {
    Unknown,
    Vertex,
    Fragment
};

class ShaderProgram {
public:
    ShaderProgram(std::string_view vs, std::string_view fs);
    ~ShaderProgram();

    void use() const;
    [[nodiscard]] uint32_t id() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    void create_program(std::string_view vs, std::string_view fs);
    [[nodiscard]] uint32_t compile_shader(std::string_view source, ShaderType type) const;
    void check_errors(uint32_t object, ShaderType type) const;

    uint32_t _id{};
    uint32_t _vertexShader{};
    uint32_t _fragmentShader{};
};


#endif//LEARN_SHADER_H
