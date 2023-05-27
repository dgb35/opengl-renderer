#ifndef LEARN_VERTEX_BUFFER_H
#define LEARN_VERTEX_BUFFER_H

#include "buffer.h"

class VertexBuffer : public IBuffer {
    uint32_t _rendererId;

public:
    VertexBuffer(const void *data, uint32_t size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};


#endif//LEARN_VERTEX_BUFFER_H
