#ifndef __QUAD_HPP__
#define __QUAD_HPP__

#include <GL/glew.h>
#include <memory>
#include "shader.hpp"

#define UNBIND  0

#define APPLE   0
#define BANNANA 1
#define GRAPE   2
#define PEAR    3
#define ORANGE  4


class Block {
	
private:
	static
	GLuint indices[];

	GLuint VAO, VBO, EBO;

	GLfloat w, h;

	GLuint shader;
	
	GLuint _fruit;
	
public:
	Block(GLfloat x, GLfloat y,
		  GLfloat h, GLfloat w,
		  GLuint vert, GLuint frag,
		  GLuint fruit);
	~Block();

	void
	Relocate(GLfloat x, GLfloat y);

	void
	Render();

	GLuint
	fruit();
};

#endif  //__QUAD_HPP__
