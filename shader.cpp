#include "shader.hpp"

using namespace std;

GLuint
readCompile(const GLchar* path, GLuint type) {
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
	
	GLuint compiled = glCreateShader(type);

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
