#pragma once
#include "glad/glad.h"
#include <iostream>
#include "glm/glm.hpp"

#define LOG(x) std::cout << #x << " = " << x << std::endl

#define glCheckError() glCheckError_(__FILE__, __LINE__)

void glClearError();

GLenum glCheckError_(const char *file, int line);

void showvec3(glm::vec3 &v);
