#pragma once
#include "glad/glad.h"
#include <iostream>

#define LOG(x) std::cout << #x << " = " << x << std::endl

#define glCheckError() glCheckError_(__FILE__, __LINE__)

void glClearError();

GLenum glCheckError_(const char *file, int line);