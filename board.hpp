#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "tile.hpp"

// this manages the board state
// contains info about the 
class Board {
private:
	// contains info about the size of the board
	// spawn rows do not render but are still active
	GLuint spawnRows;
	GLuint rows;
	GLuint cols;

public:
	// the actual board state
	Tile** board;

	Board(GLuint rows, GLuint cols, GLuint spawnRows);
	~Board();

	// returns occupant of position (row, column), or NULL if empty
	Tile* at(GLuint row, GLuint col);
	GLboolean set(GLuint row, GLuint col, Tile* val);

	void Render();
};
#endif // __BOARD_HPP__
