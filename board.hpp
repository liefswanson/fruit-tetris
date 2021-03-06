#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <thread>
#include "tile.hpp"
#include "rangeMap.hpp"

// this manages the board state
// contains info about the contents of each tile 
class Board {
private:
	// contains info about the size of the board
	// spawn rows do not render but are still active
	RangeMap* xposition;
	RangeMap* yposition;
	RangeMap* xpercent;
	RangeMap* ypercent;
	
	GLuint spawnRows;
	GLuint rows;
	GLuint cols;

	const GLuint CHAIN_LENGTH = 3; 




public:
	// the actual board state
	Tile** board;

	Board(GLuint rows, GLuint cols, GLuint spawnRows,
		  GLfloat percentInsideMarginsHeight, GLfloat percentInsideMarginsWidth);
	~Board();

	// returns occupant of position (row, column), or NULL if empty
	GLboolean on(GLuint row, GLuint col);
	Tile*     at    (GLuint row,   GLuint col);
	Tile*     makeAt(GLuint row,   GLuint col,
					 GLfloat vert, GLfloat frag, GLuint fruit);
	void      set   (GLuint row,   GLuint col,
					 Tile* val);
	
	void Render();

	Tile**         ScanForFullRows();
	Tile**         ScanForFruitChainsCols();
	Tile**         ScanForFruitChainsRows();
	Tile**         MergeDiffs(Tile** a, Tile** b);
	GLboolean      validateDiff(Tile** diff);
	void           RemoveDiff(Tile** diff);
	void           debugDiff(Tile** diff);

	GLuint SpawnRows();
	GLuint Rows();
	GLuint Cols();

	GLuint fruit();

	void clear();
};
#endif // __BOARD_HPP__
