#include "vao.h"
#include "vbo.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(const VertexBuffer &vbo, const VertexBufferLayout &layout)
{
    glGenVertexArrays(1, &id);
    AddBuffer(vbo, layout);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
}

void
VertexArray::Bind()
{
    glBindVertexArray(id);
}

void
VertexArray::UnBind()
{
    glBindVertexArray(0);
}

void
VertexArray::AddBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout)
{
    Bind();
    vbo.Bind();
    const auto &elements = layout.GetElements();
    unsigned int offset  = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i, element.count, element.type, element.normalized, layout.GetStride(), (const void *)offset);
        offset += element.count * element.GetSizeOfType(element.type);
    }
}