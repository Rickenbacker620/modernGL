#include "vbo.h"
#include <vector>

void
VertexBufferLayout::Pushfloat(unsigned int count)
{
    elements.push_back({GL_FLOAT, count, false});
    stride += sizeof(float) * count;
}

void
VertexBufferLayout::Pushint(unsigned int count)
{
    elements.push_back({GL_UNSIGNED_INT, count, false});
    stride += sizeof(unsigned int) * count;
}

void
VertexBufferLayout::Pushchar(unsigned int count)
{
    elements.push_back({GL_UNSIGNED_BYTE, count, true});
    stride += sizeof(char) * count;
}

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &id);
};

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    glGenBuffers(1, &id);
    AddVertex(data, size);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

void
VertexBuffer::AddVertex(const void *data, unsigned int size)
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void
VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void
VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
