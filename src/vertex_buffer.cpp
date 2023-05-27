#include "vertex_buffer.h"
#include <glad/gl.h>

VertexBuffer::VertexBuffer(const void *data, uint32_t size): _rendererId{}
{
    glGenBuffers(1, &_rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &_rendererId);
}
