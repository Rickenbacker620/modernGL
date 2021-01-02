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

Shader::Shader() : id(0) { Bind(); }

Shader::Shader(const std::string &path) : id(0) {
    ShaderProgramSource source = ParseShader(path);
    ProcessSource(source);
    Bind();
}

Shader::Shader(const std::string &pathv, const std::string &pathf) : id(0) {
    ShaderProgramSource source = ParseShader(pathv, pathf);
    ProcessSource(source);
    Bind();
}

Shader::~Shader() { glDeleteProgram(id); }

void Shader::Bind() const { glUseProgram(id); }

void Shader::Unbind() const { glUseProgram(0); }

void Shader::AddSource(const std::string &path) {
    ShaderProgramSource source = ParseShader(path);
    ProcessSource(source);
    Bind();
}
void Shader::AddSource(const std::string &pathv, const std::string &pathf) {
    ShaderProgramSource source = ParseShader(pathv, pathf);
    ProcessSource(source);
    Bind();
}

void Shader::SetUniform3f(const std::string &name, glm::vec3 value) {
    glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetUniform4f(const std::string &name, glm::vec4 value) {
    glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetUniformMatrix4f(const std::string &name, glm::mat4 value) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE,
                       glm::value_ptr(value));
}

unsigned int Shader::CompileShader(unsigned int type,
                                   const std::string &source) {
    int success;
    char log[512];
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl
                  << log << std::endl;
    };
    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string &path) {
    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
    std::ifstream shaderfile(path);
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(shaderfile, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        } else {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

ShaderProgramSource Shader::ParseShader(const std::string &pathv,
                                        const std::string &pathf) {
    std::ifstream vertexfile(pathv);
    std::ifstream fragfile(pathf);
    std::string line;
    std::stringstream ss[2];
    while (getline(vertexfile, line)) {
        ss[0] << line << '\n';
    }
    while (getline(fragfile, line)) {
        ss[1] << line << '\n';
    }
    return {ss[0].str(), ss[1].str()};
}

int Shader::GetUniformLocation(const std::string &name) {
    if (cache.find(name) != cache.end())
        return cache[name];
    int location = glGetUniformLocation(id, name.c_str());
    cache[name] = location;
    return location;
}

void Shader::ProcessSource(ShaderProgramSource &src) {
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, src.VSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, src.FSource);
    id = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    glDeleteShader(vs);
    glDeleteShader(fs);
}