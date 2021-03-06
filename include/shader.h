#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>

class Shader
{
  public:
    Shader();
    Shader(const std::string &path);
    Shader(const std::string &pathv, const std::string &pathf);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void AddSource(const std::string &path);
    void AddSource(const std::string &pathv, const std::string &pathf);

    int GetUniformLocation(const std::string &name);
    void SetUniform3f(const std::string &name, glm::vec3 value);
    void SetUniform4f(const std::string &name, glm::vec4 value);
    void SetUniformMatrix4f(const std::string &name, glm::mat4 value);

  private:
    unsigned int id = 0;
    std::unordered_map<std::string, int> cache;
    unsigned int CompileShader(unsigned int type, const std::string &source);
    std::pair<std::string, std::string> ParseShader(const std::string &path);
    std::pair<std::string, std::string> ParseShader(const std::string &pathv, const std::string &pathf);
    void ProcessSource(std::pair<std::string, std::string> &&src);
};
