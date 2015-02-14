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

	GLuint         ReadCompile(const GLchar* Path);

	void           Attach(GLuint shaderRef);
	void           Link();
	void           Use();
	
};
#endif	// __SHADER_HPP__
