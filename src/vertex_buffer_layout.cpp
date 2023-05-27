#include "vertex_buffer_layout.h"

void VertexBufferLayout::setAttribIndex(uint32_t index) {
    _attribIndex = index;
}

uint32_t VertexBufferLayout::attribIndex() const {
    return _attribIndex;
}
