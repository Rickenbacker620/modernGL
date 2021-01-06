#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class ElementBuffer
{
  public:
    ElementBuffer();
    ElementBuffer(const unsigned int *data, unsigned int count);
    ~ElementBuffer();

    void Bind() const;
    void Unbind() const;
    void AddIndex(const unsigned int *data, unsigned int count);
    unsigned int GetCount() const
    {
        return count;
    }

  private:
    unsigned int id    = 0;
    unsigned int count = 0;
};