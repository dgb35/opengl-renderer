#ifndef LEARN_VERTEX_ARRAY_H
#define LEARN_VERTEX_ARRAY_H


#include "buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
private:
    uint32_t _rendererId{};

public:
    VertexArray();
    ~VertexArray();

    void add_buffer(const IBuffer &buffer, const VertexBufferLayout &layout) const;

    void bind() const;
    void unbind() const;
};


#endif//LEARN_VERTEX_ARRAY_H
