#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>

struct VertexBufferElement {
    GLenum type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        return 0;
    }
};

class VertexBufferLayout {
public:
    VertexBufferLayout() : stride(0) {}

    void Pushfloat(unsigned int count);
    void Pushint(unsigned int count);
    void Pushchar(unsigned int count);

    inline unsigned int GetStride() const { return stride; }
    inline const std::vector<VertexBufferElement> &GetElements() const {
        return elements;
    }

private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
};

class VertexBuffer {
public:
    VertexBuffer();
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void AddVertex(const void *data, unsigned int size);
    void Bind() const;
    void Unbind() const;

private:
    unsigned int id;
};