#include "model.h"
#include "glad/glad.h"

using namespace std;

Model::Model()
    : vao(make_unique<VertexArray>()), vbo(make_unique<VertexBuffer>()), ebo(make_unique<ElementBuffer>()),
      layout(make_unique<VertexBufferLayout>()), shader(make_unique<Shader>())
{
}

void
Model::SetVertex(const void *data, unsigned int size)
{
    vbo->AddVertex(data, size);
}

void
Model::SetLayout(initializer_list<LayoutElement> elements)
{
    for (auto element = elements.begin(); element != elements.end(); element++)
    {
        if (element->second == "float")
            layout->Pushfloat(element->first);
        else if (element->second == "int")
            layout->Pushint(element->first);
        else if (element->second == "char")
            layout->Pushchar(element->first);
    }
    ConfigVao();
}

void
Model::ConfigVao()
{
    vao->AddBuffer(*vbo, *layout);
}

void
Model::SetIndex(const unsigned int *data, unsigned int count)
{
    ebo->AddIndex(data, count);
}

void
Model::SetShader(const string &path)
{
    shader->AddSource(path);
}

void
Model::SetShader(const string &pathv, const string &pathf)
{
    shader->AddSource(pathv, pathf);
}

void
Model::BindAll() const
{
    vao->Bind();
    shader->Bind();
}

void
Model::SetModel(glm::mat4 mat)
{
    shader->Bind();
    modelmat = mat;
    shader->SetUniformMatrix4f("model", modelmat);
}

void
Model::HookCamera(Camera &camera)
{
    shader->Bind();
    shader->SetUniformMatrix4f("view", camera.GetViewMatrix());
    shader->SetUniformMatrix4f("projection", camera.GetProjMatrix());
}

void
Model::SetUniform3f(const string &name, glm::vec3 value)
{
    shader->Bind();
    glUniform3fv(shader->GetUniformLocation(name), 1, glm::value_ptr(value));
}

void
Model::SetUniform4f(const string &name, glm::vec4 value)
{
    shader->Bind();
    glUniform4fv(shader->GetUniformLocation(name), 1, glm::value_ptr(value));
}

void
Model::SetUniformMatrix4f(const string &name, glm::mat4 value)
{
    shader->Bind();
    glUniformMatrix4fv(shader->GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
