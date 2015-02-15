#include "board.hpp"

Board::Board(GLuint rows, GLuint cols, GLuint spawnRows) {
	this->rows      = rows;
	this->cols      = cols;
	this->spawnRows = spawnRows;

	board = new Tile* [cols*(rows+spawnRows)];
}

Board::~Board() {
	for (GLuint c = 0; c < rows; ++c) {
		for (GLuint r = 0; r < rows; ++r) {
			Tile* current = this->at(r,c);
			if (current != NULL){
				delete current;
			}
		}
	}
}

Tile*
Board::at(GLuint row, GLuint col) {
	if (row > rows || col > cols ) {
		return NULL;
	}
	
	return board[cols*row + col];
}

void
Board::Render() {
	for (GLuint col = 0; col < cols; ++col) {
		for (GLuint row = spawnRows; row < rows; ++row) {
			Tile* current = this->at(row, col);
			if (current != NULL) {
				//FIXME screen size hack pass in real values
				current->Relocate(col * 5.f, (row - spawnRows) * 10.f);
				current->Render();
			}
		}
	}
}
