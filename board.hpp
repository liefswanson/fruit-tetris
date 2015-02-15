#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "tile.hpp"


class Board {
private:
	GLuint spawnRows;
	GLuint rows;
	GLuint cols;

public:
	//Tile*** spawn;
	Tile** board;

	Board(GLuint rows, GLuint cols, GLuint spawnRows);
	~Board();

	Tile* at(GLuint row, GLuint col);

	void Render();
};
#endif // __BOARD_HPP__
