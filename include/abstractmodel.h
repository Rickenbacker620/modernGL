#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/matrix_transform_2d.hpp"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shader.h"
#include "camera.h"

class Model
{
  public:
    Model()          = default;
    virtual ~Model() = default;

    virtual void SetVertex(const void *data, unsigned int size);
    virtual void SetIndex(const unsigned int *data, unsigned int count);
    virtual void SetShader(const std::string &path);
    virtual void SetShader(const std::string &pathv, const std::string &pathf);
    virtual void ConfigVao();
    virtual void SetLayout()    = 0;
    virtual void DrawTriangle() = 0;
    virtual void SetModelMatrix(glm::mat4 modelmat);
    virtual void SetVPMatrix(Camera &camera);
    virtual void Render() = 0;
    virtual void SetUniform3f(const std::string &name, glm::vec3 value);
    virtual void SetUniform4f(const std::string &name, glm::vec4 value);
    virtual void SetUniformMatrix4f(const std::string &name, glm::mat4 value);

  protected:
    VertexArray vao;
    VertexBufferLayout layout;
    VertexBuffer vbo;
    ElementBuffer ebo;
    Shader shader;
    glm::mat4 modelmat;
};