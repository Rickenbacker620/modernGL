#include "texture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <array>

std::array<GLenum, 16> Texture::pool = {
    GL_TEXTURE0,
    GL_TEXTURE1,
    GL_TEXTURE2,
    GL_TEXTURE3,
    GL_TEXTURE4,
    GL_TEXTURE5,
    GL_TEXTURE6,
    GL_TEXTURE7,
    GL_TEXTURE8,
    GL_TEXTURE9,
    GL_TEXTURE10,
    GL_TEXTURE11,
    GL_TEXTURE12,
    GL_TEXTURE13,
    GL_TEXTURE14,
    GL_TEXTURE15,
};

int Texture::poolpivot = 0;

Texture::Texture(const std::string &path, const GLint &mode)
{
    glActiveTexture(getEmpty());
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Fail to load texture" << std::endl;
    }
    stbi_image_free(data);
}
const void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}
const void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::Config()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GLenum Texture::getEmpty()
{
    //TODO suppose to be a better way(e.g itarator)
    return pool[poolpivot++];
}
