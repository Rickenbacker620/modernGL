#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/matrix_transform_2d.hpp"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shader.h"
#include "camera.h"
#include <memory>

using std::initializer_list;
using std::pair;
using std::string;
using std::unique_ptr;

typedef pair<int, string> LayoutElement;

class Model
{
  public:
    Model();
    virtual ~Model() = default;

    // vbo
    virtual void SetVertex(const void *data, unsigned int size);

    // layout
    virtual void SetLayout(initializer_list<LayoutElement>);

    // vao
    virtual void ConfigVao();

    // ebo
    virtual void SetIndex(const unsigned int *data, unsigned int count);

    // shader
    virtual void SetShader(const string &path);
    virtual void SetShader(const string &pathv, const string &pathf);

    virtual void BindAll() const;

    virtual void DrawTriangle() = 0;
    virtual void Render()       = 0;

    virtual void SetModel(glm::mat4 modelmat);
    virtual void HookCamera(Camera &camera);

    virtual void SetUniform3f(const string &name, glm::vec3 value);
    virtual void SetUniform4f(const string &name, glm::vec4 value);
    virtual void SetUniformMatrix4f(const string &name, glm::mat4 value);

  private:
    unique_ptr<VertexBuffer> vbo;
    unique_ptr<VertexBufferLayout> layout;
    unique_ptr<VertexArray> vao;
    unique_ptr<ElementBuffer> ebo;
    unique_ptr<Shader> shader;
    glm::mat4 modelmat;
};