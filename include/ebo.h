#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class ElementBuffer
{
public:
    ElementBuffer() = default;
    ElementBuffer(const unsigned int *data, unsigned int count);
    ~ElementBuffer();

    void Bind() const;
    void Unbind() const;
    void AddIndex(const unsigned int *data, unsigned int count);
    inline unsigned int GetCount() const
    {
        return count;
    }

private:
    unsigned int id;
    unsigned int count;
};