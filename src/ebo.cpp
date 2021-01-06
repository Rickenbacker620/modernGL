#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ebo.h"

ElementBuffer::ElementBuffer()
{
    glGenBuffers(1, &id);
}

ElementBuffer::ElementBuffer(const unsigned int *data, unsigned int count) : count(count)
{
    glGenBuffers(1, &id);
    AddIndex(data, count);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &id);
}

void
ElementBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void
ElementBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void
ElementBuffer::AddIndex(const unsigned int *data, unsigned int count)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}