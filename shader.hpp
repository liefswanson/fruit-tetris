#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {

private:
	GLuint Program;
	
public:
	Shader();

	void           Attach(GLuint shaderRef);
	void           Link();
	void           Use();
	GLuint         ref();
};

GLuint             readCompile(const GLchar* Path,
							   GLuint type);
#endif	// __SHADER_HPP__
