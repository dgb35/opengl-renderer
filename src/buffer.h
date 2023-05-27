#ifndef LEARN_BUFFER_H
#define LEARN_BUFFER_H

#include <cstdint>

class IBuffer {
public:
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};

#endif//LEARN_BUFFER_H
