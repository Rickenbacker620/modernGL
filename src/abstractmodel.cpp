#include "abstractmodel.h"
#include "glad/glad.h"

void
Model::SetVertex(const void *data, unsigned int size)
{
    vbo.AddVertex(data, size);
}

void
Model::SetIndex(const unsigned int *data, unsigned int count)
{
    ebo.AddIndex(data, count);
}

void
Model::SetShader(const std::string &path)
{
    shader.AddSource(path);
}

void
Model::SetShader(const std::string &pathv, const std::string &pathf)
{
    shader.AddSource(pathv, pathf);
}

void
Model::SetModelMatrix(glm::mat4 modelmat)
{
    shader.Bind();
    modelmat = modelmat;
    shader.SetUniformMatrix4f("model", modelmat);
}

void
Model::SetVPMatrix(Camera &camera)
{
    shader.Bind();
    shader.SetUniformMatrix4f("view", camera.GetViewMatrix());
    shader.SetUniformMatrix4f("projection", camera.GetProjMatrix());
}

void
Model::SetUniform3f(const std::string &name, glm::vec3 value)
{
    shader.Bind();
    glUniform3fv(shader.GetUniformLocation(name), 1, glm::value_ptr(value));
}

void
Model::SetUniform4f(const std::string &name, glm::vec4 value)
{
    shader.Bind();
    glUniform4fv(shader.GetUniformLocation(name), 1, glm::value_ptr(value));
}

void
Model::SetUniformMatrix4f(const std::string &name, glm::mat4 value)
{
    shader.Bind();
    glUniformMatrix4fv(shader.GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void
Model::ConfigVao()
{
    vao.AddBuffer(vbo, layout);
}
