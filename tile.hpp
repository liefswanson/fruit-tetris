#ifndef __TILE_HPP__
#define __TILE_HPP__

#include <GL/glew.h>
#include <memory>
#include <iostream>

#define UNBIND  0

#define NONE    0

#define APPLE   1
#define BANANA  2
#define GRAPE   3
#define PEAR    4
#define ORANGE  5

#define FRUITS  6

// this is an abstraction used to render rectangles by height width and (x, y) position 
class Tile {
	
private:
	// for initializing each rectangle's ebo
	static
	GLuint indices[];

	GLuint VAO, VBO, EBO;

	// height and width
	// x and y are used 
	GLfloat w, h;

	// shader to use when rendering this rectangle
	// each rectangle only has one shader, and each shader only has one rectangle
	GLuint shader;

	GLuint _fruit;


public:
	Tile(GLfloat x, GLfloat y,
		 GLfloat h, GLfloat w,
		 GLuint vert, GLuint frag,
		 GLuint fruit);
	Tile(const Tile &that);
	~Tile();

	// sends info to shader about how to move this rectangle's position
	void
	Relocate(GLfloat x, GLfloat y);

	void
	Render();
	// observe the type of the fruit
	GLuint fruit();
};

#endif  //__TILE_HPP__
