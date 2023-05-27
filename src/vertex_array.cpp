#include "vertex_array.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &_rendererId);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &_rendererId);
}

void VertexArray::add_buffer(const IBuffer &buffer, const VertexBufferLayout &layout) const {
    bind();
    buffer.bind();
    const auto &elements = layout.elements();
    uint32_t offset = 0;
    for (uint32_t i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(layout.attribIndex(), element.count, element.type, element.normalized, layout.stride(), (const void *) offset);
        offset = element.count * VertexBufferElement::type_size(element.type);
    }
}

void VertexArray::bind() const {
    glBindVertexArray(_rendererId);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
