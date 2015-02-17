#ifndef __BOARD_HPP__
#define __BOARD_HPP__


#include <algorithm>
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

public:
	// the actual board state
	Tile** board;

	Board(GLuint rows, GLuint cols, GLuint spawnRows,
		  GLfloat percentInsideMarginsHeight, GLfloat percentInsideMarginsWidth,
		  GLfloat hwRatio);
	~Board();

	// returns occupant of position (row, column), or NULL if empty
	Tile*     at    (GLuint row, GLuint col);
	Tile*     makeAt(GLuint row, GLuint col,
					 GLfloat vert, GLfloat frag, GLuint fruit);
	GLboolean set   (GLuint row, GLuint col,
					 Tile* val);
	
	
	GLboolean      canMoveD(GLuint row, GLuint col);
	GLboolean      canMoveL(GLuint row, GLuint col);
	GLboolean      canMoveR(GLuint row, GLuint col);
	void           moveD   (GLuint row, GLuint col);
	void           moveL   (GLuint row, GLuint col);
	void           moveR   (GLuint row, GLuint col);

	void Render();

	GLuint SpawnRows();
	GLuint Rows();
	GLuint Cols();
};
#endif // __BOARD_HPP__
