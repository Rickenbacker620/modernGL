#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "abstractmodel.h"
#include "cubemodel.h"

GLFWwindow *CreateApp(const std::string &title,
                      const int &width,
                      const int &height,
                      GLFWkeyfun key,
                      GLFWcursorposfun mouse,
                      GLFWscrollfun scroll);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);