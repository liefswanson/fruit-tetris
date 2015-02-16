#include "board.hpp"

Board::Board(GLuint rows, GLuint cols, GLuint spawnRows,
			 GLfloat percentInsideMarginsHeight, GLfloat percentInsideMarginsWidth,
			 GLfloat hwRatio) {
	this->rows      = rows;
	this->cols      = cols;
	this->spawnRows = spawnRows;

	board = new Tile* [cols*(rows+spawnRows)];

	for (GLuint i = 0; i < cols*(rows+spawnRows); ++i) {
		board[i] = NULL;
	}

	xposition = new RangeMap(0, 100, -percentInsideMarginsWidth,      percentInsideMarginsWidth);
	yposition = new RangeMap(0, 100,  percentInsideMarginsHeight,    -percentInsideMarginsHeight);
	xpercent  = new RangeMap(0, 100,  0,                          2 * percentInsideMarginsWidth);
	ypercent  = new RangeMap(0, 100,  0,                          2 * percentInsideMarginsHeight);
}

Board::~Board() {
	for (GLuint i = 0; i < cols*(rows + spawnRows); ++i) {
		if (board[i] != NULL){
			delete board[i];
		}
	}
	delete[] board;
	delete xposition;
	delete xpercent;
	delete yposition;
	delete ypercent;
}

Tile*
Board::at(GLuint row, GLuint col) {
	if (row > rows || col > cols ) {
		std::cout << "tried to get outside grid " << row << ' ' << col << std::endl;
		return NULL;
	}
	return board[cols*row + col];
}

Tile*
Board::makeAt(GLuint row, GLuint col, GLfloat vert, GLfloat frag, GLuint fruit){
	auto temp = at(row, col);
	if (temp == NULL) {
		set(row, col,
			new Tile(0,0,
					 xpercent->map(100.f/cols),
					 ypercent->map(100.f/rows),
					 vert, frag, fruit));
		return at(row, col);
	} else {
		std::cout << "tried to place outside grid " << row << ' ' << col << std::endl;
		return NULL;	
	} 
}

GLboolean
Board::set(GLuint row, GLuint col, Tile* val) {
	if (at(row, col) != NULL ) {
		return GL_FALSE;
	}
	board[cols*row + col] = val;
	return GL_TRUE;
}

GLboolean
Board::canMoveD(GLuint row, GLuint col) {
	return GL_TRUE;

}


GLboolean
Board::canMoveL(GLuint row, GLuint col) {
	return GL_TRUE;

}


GLboolean
Board::canMoveR(GLuint row, GLuint col) {
	return GL_TRUE;
	
}


void
Board::moveD(GLuint row, GLuint col) {
	
}



void
Board::moveL(GLuint row, GLuint col) {
	
}


void
Board::moveR(GLuint row, GLuint col) {
	
}


void
Board::Render() {
	for (GLuint col = 0; col < cols; ++col) {
		for (GLuint row = spawnRows; row < rows; ++row) {
			Tile* current = this->at(row, col);
			if (current != NULL) {
				//FIXME screen size hack pass in real values
				//std::cout << row << ' ' << col  << std::endl;
				current->Relocate(xposition->map(col * 100.f/cols), yposition->map((row - spawnRows) * 100.f/rows));
				current->Render();
			}
		}
	}
}
