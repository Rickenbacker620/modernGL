#include "cubemodel.h"

void
Cube::SetLayout()
{
    layout.Pushfloat(3);
}

void
Cube::DrawTriangle()
{
    vao->Bind();
    shader.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void
Cube::Render()
{
}