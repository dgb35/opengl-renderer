#include "index_buffer.h"
#include <glad/gl.h>

IndexBuffer::IndexBuffer(const void *data, uint32_t count) : _rendererId{}, _count{count}
{
    static_assert(sizeof(uint32_t) == sizeof(GLuint));

    glGenBuffers(1, &_rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &_rendererId);
}

uint32_t IndexBuffer::count() const {
    return _count;
}
