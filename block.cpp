#include "block.hpp"

Block::Block(Board* board){
	this->board = board;
	auto shape = rand() % SHAPES;

	switch(shape) {
	case ELBOW:
		makeElbow();
		break;
	case LINE:
		makeLine();
		break;
	case BEND:
		makeBend();
		break;
	}
}


Block::~Block(){
	
}

GLboolean
Block::rotW(){
	
}

GLboolean
Block::rotC(){
	
}
 
GLboolean
Block::moveL(){
	
}

GLboolean
Block::moveR(){
	
}

GLboolean
Block::moveD(){
	
}

void
Block::sortD(){
	
}

void
Block::sortL(){
	
}

void
Block::sortR(){
	
}

void
Block::sortC(){
	
}

void
Block::sortW(){
	
}

GLboolean
Block::in(GLuint row, GLuint col) {
	
}

void
Block::makeElbow(){
	
}

void
Block::makeLine(){
	
}

void
Block::makeBend(){
	
}
