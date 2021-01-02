#pragma once
#include "abstractmodel.h"

class Cube : public Model
{
public:
    Cube() = default;
    void SetLayout();
    VertexBufferLayout &GetLayout()
    {
        return layout;
    }
    void DrawTriangle();
    void Render();

private:
};