#ifndef __TILE_HPP__
#define __TILE_HPP__

#include <GL/glew.h>
#include <memory>
#include "shader.hpp"

#define UNBIND  0

#define APPLE   0
#define BANANA  1
#define GRAPE   2
#define PEAR    3
#define ORANGE  4


class Tile {
	
private:
	static
	GLuint indices[];

	GLuint VAO, VBO, EBO;

	GLfloat w, h;

	GLuint shader;
	
	GLuint _fruit;
	
public:
	Tile(GLfloat x, GLfloat y,
		  GLfloat h, GLfloat w,
		  GLuint vert, GLuint frag,
		  GLuint fruit);
	~Tile();

	void
	Relocate(GLfloat x, GLfloat y);

	void
	Render();

	GLuint
	fruit();
};

#endif  //__TILE_HPP__
