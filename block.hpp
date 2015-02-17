#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <GL/glew.h>
#include <cstdlib>
#include "board.hpp"
#include "tile.hpp"

#define ELBOW  0
#define LINE   1
#define BEND   2

#define SHAPES 3

// used to give the player a way to control the pieces falling from the top of the board
// all this does is control where the tiles are located on the board until they can no longer move
class Block {
private:
	const static GLuint TILES_PER_BLOCK = 4;
	const static GLuint r = 0;
	const static GLuint c = 1;
	// coordinates of the pieces in the block by row and column
	GLuint RCs[TILES_PER_BLOCK][2];

	GLuint frags[6];

	GLuint vert;
	
	// pointer to the board the block is bound to
	Board* board;

	void makeElbow();
	void makeLine();
	void makeBend();
	
	void      sortD();
	void      sortL();
	void      sortR();
	void      sortC();
	void      sortW();
	
	GLboolean in(GLuint row, GLuint col);
public:
	Block(Board* board );
	~Block();
	
	GLboolean rotW();
	GLboolean rotC();
	GLboolean moveL();
	GLboolean moveR();
	GLboolean moveD();



};


#endif //__BLOCK_HPP__
