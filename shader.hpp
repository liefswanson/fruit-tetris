#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

// function used to hide the ugly process of compiling a piece of a shader 
GLuint readCompile(const GLchar* Path, GLuint type);
#endif	// __SHADER_HPP__
