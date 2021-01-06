#include "cubemodel.h"

void
Cube::DrawTriangle()
{
    BindAll();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void
Cube::Render()
{
}