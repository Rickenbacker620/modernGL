#pragma once
#include "model.h"

class Cube : public Model
{
  public:
    Cube() = default;
    void DrawTriangle();
    void Render();

  private:
};