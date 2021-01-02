#pragma once
#include <string>
#include <array>
#include "glad/glad.h"

class Texture
{
public:
    Texture(const std::string &path, const GLint &mode);
    const void Bind();
    const void Unbind();
    static void Config();
    static GLenum getEmpty();

private:
    static std::array<GLenum, 16> pool;
    static int poolpivot;
    unsigned int id;
    unsigned char *data;
    int width;
    int height;
    int nrChannels;
};