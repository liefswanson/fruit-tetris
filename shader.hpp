#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

GLuint readCompile(const GLchar* Path, GLuint type);
#endif	// __SHADER_HPP__
