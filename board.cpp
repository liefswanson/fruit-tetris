#include "board.hpp"

Board::Board(GLuint rows, GLuint cols, GLuint spawnRows,
			 GLfloat percentInsideMarginsHeight, GLfloat percentInsideMarginsWidth) {
	this->rows      = rows;
	this->cols      = cols;
	this->spawnRows = spawnRows;
	
	board = new Tile* [cols*(rows)];

	for (GLuint i = 0; i < cols*(rows); ++i) {
		board[i] = NULL;
	}

	xposition = new RangeMap(0, 100, -percentInsideMarginsWidth,      percentInsideMarginsWidth);
	yposition = new RangeMap(0, 100,  percentInsideMarginsHeight,    -percentInsideMarginsHeight);
	xpercent  = new RangeMap(0, 100,  0,                          2 * percentInsideMarginsWidth);
	ypercent  = new RangeMap(0, 100,  0,                          2 * percentInsideMarginsHeight);
}

Board::~Board() {
	for (GLuint i = 0; i < cols*(rows); ++i) {
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
					 ypercent->map(100.f/(rows - spawnRows)),
					 vert, frag, fruit));
		return at(row, col);
	} else {
		std::cout << "tried to place in illegal spot " << row << ' ' << col << std::endl;
		return NULL;	
	} 
}

void
Board::set(GLuint row, GLuint col, Tile* val) {
	board[cols*row + col] = val;
}

GLboolean
Board::canMoveD(GLuint row, GLuint col) {
	auto temp = row-1;
	if (temp > rows) {
		return GL_FALSE;
	}
	if (at(temp, col) == NULL){
		return GL_TRUE;
	} else {
		return GL_FALSE;
	}
}

GLboolean
Board::canMoveL(GLuint row, GLuint col) {
	auto temp = col-1;
	if (temp > rows) {
		return GL_FALSE;
	}
	if (at(row,temp) == NULL){
		return GL_TRUE;
	} else {
		return GL_FALSE;
	}
}

GLboolean
Board::canMoveR(GLuint row, GLuint col) {
	auto temp = col+1;
	if (temp > rows) {
		return GL_FALSE;
	}
	if (at(row,temp) == NULL){
		return GL_TRUE;
	} else {
		return GL_FALSE;
	}
}

void
Board::moveD(GLuint row, GLuint col) {
	board[cols*row-1 + col] = board[cols*row + col];
	board[cols*row + col] = NULL;
}

void
Board::moveL(GLuint row, GLuint col) {
	board[cols*row + col-1] = board[cols*row + col];
	board[cols*row + col] = NULL;
}

void
Board::moveR(GLuint row, GLuint col) {
	board[cols*row + col+1] = board[cols*row + col];
	board[cols*row + col] = NULL;
}

Tile**
Board::ScanForFullRows() {
	// TODO note the use of spawnrows this may introduce bugs
	auto diff = new Tile*[cols*(rows-spawnRows)];
	for(GLuint row = spawnRows; row < rows; ++row){
		GLboolean valid = GL_TRUE;
		for(GLuint col = 0; col < cols; ++col) {
			if (board[cols*(row) + col] == NULL) {
				valid = GL_FALSE;
				break;
			} else {
				diff[cols*(row - spawnRows) + col] = board[cols*row + col];
			}
		}
		if(!valid) {
			for(GLuint col = 0; col < cols; ++col) {
				diff[cols*(row - spawnRows) + col] = NULL;
			}
		}
	}
	return diff;
}

Tile**
Board::ScanForFruitChains() {
	
	return NULL;
}

void
Board::debugDiff(Tile** diff){
	for(GLuint row = 0; row < rows-spawnRows; ++row) {
		std::cout << std::setfill(' ') << std::setw(2) << row;
		std::cout << ':';
		for(GLuint col = 0; col < cols; ++col) {
			if(diff[cols*row + col] != NULL) {
				std::cout << '+';
			} else {
				std::cout << '-';
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Tile**
Board::MergeDiffs(Tile** a, Tile** b) {
	Tile** val = new Tile* [cols*(rows-spawnRows)];
	for(GLuint i = 0; i < cols*(rows-spawnRows); i++){
		if (a[i] != NULL) {
			val[i] = a[i];
		} else {
			val[i] = b[i];
		}
	}
	return val;
}

void
Board::RemoveDiff(Tile** diff) {
	
}

void
Board::Render() {
	for (GLuint row = spawnRows; row < rows; ++row) {
		for (GLuint col = 0; col < cols; ++col) {
			Tile* current = this->at(row, col);
			if (current != NULL) {
				//FIXME screen size hack pass in real values
				//std::cout << row << ' ' << col  << std::endl;
				current->Relocate(xposition->map(col * 100.f/cols),
								  yposition->map((row - spawnRows) * 100.f/(rows - spawnRows)));
				current->Render();
			}
		}
	}
}

GLuint
Board::SpawnRows() {return spawnRows;}
GLuint
Board::Rows()      {return rows;}
GLuint
Board::Cols()      {return cols;}

GLboolean
Board::on(GLuint row, GLuint col) {
	return       row < rows &&
				 col < cols;
}
