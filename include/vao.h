#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "vbo.h"

class VertexArray
{
  public:
    VertexArray();
    VertexArray(const VertexBuffer &vbo, const VertexBufferLayout &layout);
    ~VertexArray();

    void Bind();
    void UnBind();
    void AddBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout);

  private:
    unsigned int id;
};