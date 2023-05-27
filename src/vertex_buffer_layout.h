#ifndef LEARN_VERTEX_BUFFER_LAYOUT_H
#define LEARN_VERTEX_BUFFER_LAYOUT_H

#include <cassert>
#include <glad/gl.h>
#include <utility>
#include <vector>

struct VertexBufferElement {
    uint32_t type;
    uint32_t count;
    uint8_t normalized;

    static uint32_t type_size(uint32_t type) {
        if (type == GL_FLOAT)
            return sizeof(GLfloat);
        else if (type == GL_UNSIGNED_INT)
            return sizeof(GLuint);
        else if (type == GL_UNSIGNED_BYTE)
            return sizeof(GLubyte);
        assert(false);
    }
};

class VertexBufferLayout {

private:
    std::vector<VertexBufferElement> _elements;
    uint32_t _stride;
    uint32_t _attribIndex;

public:
    explicit VertexBufferLayout() : _elements(), _stride(0), _attribIndex(0) {}

    template<typename T>
    void push(uint32_t count) {
    }

    template<>
    void push<float>(uint32_t count) {
        _elements.push_back({GL_FLOAT, count, false});
        _stride += VertexBufferElement::type_size(GL_FLOAT) * count;
    }

    template<>
    void push<unsigned int>(uint32_t count) {
        _elements.push_back({GL_UNSIGNED_INT, count, false});
        _stride += VertexBufferElement::type_size(GL_UNSIGNED_INT) * count;
    }

    template<>
    void push<unsigned char>(uint32_t count) {
        _elements.push_back({GL_UNSIGNED_BYTE, count, true});
        _stride += VertexBufferElement::type_size(GL_UNSIGNED_BYTE) * count;
    }

    void setAttribIndex(uint32_t index);
    [[nodiscard]] uint32_t attribIndex() const;

    [[nodiscard]] uint32_t stride() const { return _stride; }
    [[nodiscard]] std::vector<VertexBufferElement> elements() const { return _elements; }
};


#endif//LEARN_VERTEX_BUFFER_LAYOUT_H
