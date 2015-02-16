#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <GL/glew.h>
#include <cstdlib>
#include "board.hpp"
#include "tile.hpp"

#define ELBOW 0
#define LINE  1
#define BENT  2

// used to give the player a way to control the pieces falling from the top of the board
// all this does is control where the tiles are located on the board until they can no longer move
class Block {
private:
	// coordinates of the pieces in the block by row and column
	GLuint* rows;
	GLuint* cols;

	// pointer to the board the block is bound to
	Board* board;

	// used to randomize the shape of a piece
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
