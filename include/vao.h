#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "vbo.h"

class VertexArray {
public:
    VertexArray();
    VertexArray(const VertexBuffer &vb, const VertexBufferLayout &layout);
    ~VertexArray();

    void Bind() const;
    void UnBind() const;
    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

private:
    unsigned int id;
};