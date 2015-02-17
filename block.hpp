#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <GL/glew.h>
#include <cstdlib>
#include <algorithm>
#include "board.hpp"
#include "tile.hpp"

#define I_piece  0
#define L_piece  1
#define S_piece  2

#define SHAPES   3

#define PIECE_SIZE      5
#define TILES_PER_BLOCK 4
// used to give the player a way to control the pieces falling from the top of the board
// all this does is control where the tiles are located on the board until they can no longer move
class Block {
private:
	GLuint rowDeltaPiece;
	GLuint colDeltaPiece;
	
	GLuint rowDeltaCheck;
	GLuint colDeltaCheck;

	Tile* piece[PIECE_SIZE][PIECE_SIZE] = {};
	Tile* check[PIECE_SIZE][PIECE_SIZE] = {};

	Tile* orderPiece[4] = {};
	Tile* orderCheck[4] = {};

	GLuint frags[6];

	GLuint vert;
	
	// pointer to the board the block is bound to
	Board* board;

	GLuint randFruit();
	
	// makes the shape into that of indicated letter
	void makeI();
	void makeL();
	void makeS();
	void clear();
	
	
	GLboolean checkMove();

	// sync Piece to Check 
	void syncPiece();
	// sync Check to Piece
	void syncCheck();

	// push to and pop piece off the board
	void push();
	void pop();

	void debugBoard();

public:
	Block(Board* board, GLuint frags[], GLuint vert);
	~Block();

	// can  = check validity
	// rot  = rotate
	// move = move 
	// W = withershins
	// C = clockwise
	// L = left
	// R = right
	// D = down
	void      makeBlock();
	
	void      applyMove();
	void      discardMove();

	GLboolean canRotW();
	GLboolean canRotC();
	GLboolean canMoveL();
	GLboolean canMoveR();
	GLboolean canMoveD();

	void shuffleL();
	void shuffleR();
};


#endif //__BLOCK_HPP__
