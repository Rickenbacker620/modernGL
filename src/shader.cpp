#include "shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

Shader::Shader()
{
    Bind();
}

Shader::Shader(const string &path)
{
    AddSource(path);
}

Shader::Shader(const string &pathv, const string &pathf)
{
    AddSource(pathv, pathf);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void
Shader::Bind() const
{
    glUseProgram(id);
}

void
Shader::Unbind() const
{
    glUseProgram(0);
}

void
Shader::AddSource(const string &path)
{
    ProcessSource(ParseShader(path));
    Bind();
}
void
Shader::AddSource(const string &pathv, const string &pathf)
{
    ProcessSource(ParseShader(pathv, pathf));
    Bind();
}

void
Shader::SetUniform3f(const string &name, glm::vec3 value)
{
    glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void
Shader::SetUniform4f(const string &name, glm::vec4 value)
{
    glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void
Shader::SetUniformMatrix4f(const string &name, glm::mat4 value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int
Shader::CompileShader(unsigned int type, const string &source)
{
    int success;
    char log[512];
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 512, NULL, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << log << std::endl;
    };
    return id;
}

pair<string, string>
Shader::ParseShader(const string &path)
{
    enum class ShaderType
    {
        NONE     = -1,
        VERTEX   = 0,
        FRAGMENT = 1
    };

    std::ifstream shaderfile(path);
    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(shaderfile, line))
    {
        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

pair<string, string>
Shader::ParseShader(const string &pathv, const string &pathf)
{
    std::ifstream vertexfile(pathv);
    std::ifstream fragfile(pathf);
    string line;
    stringstream ss[2];
    while (getline(vertexfile, line))
    {
        ss[0] << line << '\n';
    }
    while (getline(fragfile, line))
    {
        ss[1] << line << '\n';
    }
    return {ss[0].str(), ss[1].str()};
}

int
Shader::GetUniformLocation(const string &name)
{
    if (cache.find(name) != cache.end())
        return cache[name];
    int location = glGetUniformLocation(id, name.c_str());
    cache[name]  = location;
    return location;
}

void
Shader::ProcessSource(pair<string, string> &&src)
{
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, src.first);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, src.second);
    id              = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    glDeleteShader(vs);
    glDeleteShader(fs);
}