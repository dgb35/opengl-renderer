#ifndef LEARN_INDEX_BUFFER_H
#define LEARN_INDEX_BUFFER_H

#include "buffer.h"

class IndexBuffer : public IBuffer {
    uint32_t _rendererId;
    uint32_t _count;

public:
    IndexBuffer(const void *data, uint32_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    [[nodiscard]] uint32_t count() const;
};


#endif// LEARN_INDEX_BUFFER_H
