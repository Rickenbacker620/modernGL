#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/matrix_transform_2d.hpp"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shader.h"
#include "camera.h"
#include <memory>

using namespace std;

class Model
{
  public:
    Model();
    virtual ~Model() = default;

    virtual void SetVertex(const void *data, unsigned int size);
    virtual void SetIndex(const unsigned int *data, unsigned int count);
    virtual void SetShader(const string &path);
    virtual void SetShader(const string &pathv, const string &pathf);
    virtual void ConfigVao();
    virtual void SetLayout()    = 0;
    virtual void DrawTriangle() = 0;
    virtual void SetModelMatrix(glm::mat4 modelmat);
    virtual void SetVPMatrix(Camera &camera);
    virtual void Render() = 0;
    virtual void SetUniform3f(const string &name, glm::vec3 value);
    virtual void SetUniform4f(const string &name, glm::vec4 value);
    virtual void SetUniformMatrix4f(const string &name, glm::mat4 value);

  protected:
    unique_ptr<VertexArray> vao;
    unique_ptr<VertexBufferLayout> layout;
    unique_ptr<VertexBuffer> vbo;
    unique_ptr<ElementBuffer> ebo;
    unique_ptr<Shader> shader;
    glm::mat4 modelmat;
};