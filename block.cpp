#include "block.hpp"

Block::Block(Board* board, GLuint frags[], GLuint vert){
	srand(time(NULL));
	this->board = board;
	this->vert = vert;
	// FIXME magic number
	for(GLuint i = 0; i < FRUITS; ++i) {
		this->frags[i] = frags[i];
	}

}


Block::~Block(){
	
}


// std::cout << row << ' ' << col << std::endl;
// std::cout << row +rowDelta << ' ' << col +colDelta << std::endl;

void
Block::applyMove(){
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			if(piece[row][col] != NULL) {
				board->set(row +rowDelta, col +colDelta, NULL);
			}
		}
	}
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			if(check[row][col] != NULL) {
			 	board->set(row +rowDelta, col +colDelta, check[row][col]);
		    }
		    piece[row][col] = check[row][col];
		}
	}
}

GLboolean
Block::checkMove() {
	GLboolean temp = GL_TRUE;
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			// if(piece[row][col] != NULL) {
				board->set(row +rowDelta, col +colDelta, NULL);
			// }
		}
	}

	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			if(check[row][col] != NULL){
				if(!board->on(row +rowDelta, col +colDelta) ||
				    board->at(row +rowDelta, col +colDelta) != NULL){
					temp = GL_FALSE;
				}
			}
		}
	}
	
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			// if(piece[row][col] != NULL) {
				board->set(row +rowDelta, col +colDelta, piece[row][col]);
			// }
		}
	}
	if(temp) {
		std::cout << "  legal move" << std::endl;
	} else {
		std::cout << "illegal move" << std::endl;
	}
	return temp;
}

GLboolean
Block::canRotW(){
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[col][PIECE_SIZE -1 -row];
		}
	}
	return checkMove();
}

GLboolean
Block::canRotC(){
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[PIECE_SIZE -1 -col][row];
		}
	}
	return checkMove();
}

GLboolean
Block::canMoveL(){
	--colDelta;
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[row][col];
		}
	}
	return checkMove();
}

GLboolean
Block::canMoveR(){
	++colDelta;
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[row][col];
		}
	}
	return checkMove();
}

GLboolean
Block::canMoveD(){
	++rowDelta;
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[row][col];
		}
	}
	return checkMove();
}

GLuint
Block::randFruit(){
	//FIXME magic number
	//auto temp = (rand() % (FRUITS -1)) +1;
	//std::cout << temp << std::endl;
	//return temp;
	return (rand() % (FRUITS -1)) +1;
}

void
Block::makeI(){
    //
	//
	// ++++
	//
	//
    //0..3, 2

	std::cout << 'I' << std::endl;
	GLuint fruit;
	fruit = randFruit();
	piece[0][2] = board->makeAt(0 +rowDelta, 2 +colDelta, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[1][2] = board->makeAt(1 +rowDelta, 2 +colDelta, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[2][2] = board->makeAt(2 +rowDelta, 2 +colDelta, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[3][2] = board->makeAt(3 +rowDelta, 2 +colDelta, vert, frags[fruit], fruit);
}

void
Block::makeL(){
	//
	//
	// +++
	// +
	//
    //1, 3
	//1..3, 2

	std::cout << 'L' << std::endl;
	GLuint fruit;
	fruit = randFruit();
	piece[1][3] = board->makeAt(1 +rowDelta, 3 +colDelta, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[1][2] = board->makeAt(1 +rowDelta, 2 +colDelta, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[2][2] = board->makeAt(2 +rowDelta, 2 +colDelta, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[3][2] = board->makeAt(3 +rowDelta, 2 +colDelta, vert, frags[fruit], fruit);
}

void
Block::makeS(){
	//
	//
	//  ++
	// ++
	// 
    //1..2, 3
	//2..3, 2


	std::cout << 'S' << std::endl;
	GLuint fruit;
	fruit = randFruit();
	piece[1][3] = board->makeAt(1 +rowDelta, 3 +colDelta, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[2][3] = board->makeAt(2 +rowDelta, 3 +colDelta, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[2][2] = board->makeAt(2 +rowDelta, 2 +colDelta, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[3][2] = board->makeAt(3 +rowDelta, 2 +colDelta, vert, frags[fruit], fruit);
}

void
Block::makeBlock(){
	this->clear();
	auto shape = rand() % SHAPES;

	switch(shape) {
	case I_piece:
		makeI();
		break;
	case L_piece:
		makeL();
		break;
	case S_piece:
		makeS();
		break;
	}
}

void
Block::clear(){
	// FIXME for testing so i can see the block
	rowDelta = 10;
	colDelta = rand() % (board->Cols() -PIECE_SIZE -1);
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			piece[row][col] = NULL;
			check[row][col] = NULL;
		}
	}
}
