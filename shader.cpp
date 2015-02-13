#include "shader.hpp"

using namespace std;

Shader::Shader(){
	this->Program = glCreateProgram();
}

GLuint
Shader::ReadCompile(const GLchar* path) {
	string source;

	try {
		stringstream temp;
		
		ifstream file(path);
		temp << file.rdbuf();
		file.close();
		source = temp.str();
		
	} catch(exception e) {
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " << path << endl;
	}

	const GLchar* charSource = source.c_str();
	
	GLuint compiled = 0;


	const GLchar* ext = strrchr(path, '.');


	// determine the type of shader
	if (strcmp(ext, ".vert") == 0) {
		compiled = glCreateShader(GL_VERTEX_SHADER);
	} else if (strcmp(ext, ".frag") == 0) {
		compiled = glCreateShader(GL_FRAGMENT_SHADER);
	} else {
		//? non glsl file input
	}

	glShaderSource(compiled, 1, &charSource, NULL);
	glCompileShader(compiled);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(compiled, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(compiled, 512, NULL, infoLog);
		cout << "ERROR::SHADER::" << path << "::COMPILATION_FAILED\n" << infoLog << endl;
	}
	
	return compiled;
}

void
Shader::Attach(GLuint shaderRef) {
	glAttachShader(this->Program, shaderRef);
}

void
Shader::Link() {
	glLinkProgram(this->Program);
	
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
}

void
Shader::Use() {
	glUseProgram(this->Program);
}
