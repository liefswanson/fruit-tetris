#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <GL/glew.h>
#include <cstdlib>
#include "board.hpp"
#include "tile.hpp"

#define ELBOW 0
#define LINE  1
#define BENT  2

class Block {
private:
	GLuint* xs;
	GLuint* ys;

	Board* board;

	void
	randomizePiece();
	
public:
	Block();
	~Block();

	GLboolean
	rotateLeft();

	GLboolean
	rotateRight();

	GLboolean
	moveLeft();

	GLboolean
	moveRight();

	GLboolean
	moveDown();
};


#endif //__BLOCK_HPP__
