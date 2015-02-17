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

void
Block::applyMove(){
	pop();
	debugBoard();
	syncPiece();
	push();
	debugBoard();
}

void
Block::discardMove(){
	syncCheck();
}

GLboolean
Block::checkMove() {
	GLboolean temp = GL_TRUE;
	pop();
	debugBoard();

	
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			if(check[row][col] != NULL){
				if(!board->on(row +rowDeltaCheck +board->SpawnRows(), col +colDeltaCheck) ||
				    board->at(row +rowDeltaCheck +board->SpawnRows(), col +colDeltaCheck) != NULL){
					temp = GL_FALSE;
				}
			}
		}
	}
	push();
	debugBoard();
	
	if(temp) {
		std::cout << "legal move" << std::endl;
	} else {
		std::cout << "illegal move" << std::endl;
	}
	return temp;
}


// FIXME possible issue with the order of sync
// use function instead
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
	syncCheck();
	--colDeltaCheck;
	return checkMove();
}

GLboolean
Block::canMoveR(){
	syncCheck();
	++colDeltaCheck;
	return checkMove();
}

GLboolean
Block::canMoveD(){
	syncCheck();
	++rowDeltaCheck;
	return checkMove();
}

GLuint
Block::randFruit(){
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
	piece[0][2] = board->makeAt(0 +rowDeltaPiece, 2 +colDeltaPiece, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[1][2] = board->makeAt(1 +rowDeltaPiece, 2 +colDeltaPiece, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[2][2] = board->makeAt(2 +rowDeltaPiece, 2 +colDeltaPiece, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[3][2] = board->makeAt(3 +rowDeltaPiece, 2 +colDeltaPiece, vert, frags[fruit], fruit);
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
	piece[1][3] = board->makeAt(1 +rowDeltaPiece, 3 +colDeltaPiece, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[1][2] = board->makeAt(1 +rowDeltaPiece, 2 +colDeltaPiece, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[2][2] = board->makeAt(2 +rowDeltaPiece, 2 +colDeltaPiece, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[3][2] = board->makeAt(3 +rowDeltaPiece, 2 +colDeltaPiece, vert, frags[fruit], fruit);
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
	piece[1][3] = board->makeAt(1 +rowDeltaPiece, 3 +colDeltaPiece, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[2][3] = board->makeAt(2 +rowDeltaPiece, 3 +colDeltaPiece, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[2][2] = board->makeAt(2 +rowDeltaPiece, 2 +colDeltaPiece, vert, frags[fruit], fruit);
	fruit = randFruit();
	piece[3][2] = board->makeAt(3 +rowDeltaPiece, 2 +colDeltaPiece, vert, frags[fruit], fruit);
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
	rowDeltaPiece = 10;
	colDeltaPiece = rand() % (board->Cols() -PIECE_SIZE -1);
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			piece[row][col] = NULL;
		}
	}
	syncCheck();
}

void
Block::syncPiece(){
	std::cout << "sync piece" << std::endl;
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			piece[row][col] = check[row][col];
		}
	}
	rowDeltaPiece = rowDeltaCheck;
	colDeltaPiece = colDeltaCheck;
}

void
Block::syncCheck(){
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[row][col] ;
		}
	}
	rowDeltaCheck = rowDeltaPiece;
	colDeltaCheck = colDeltaPiece;
}

void
Block::push(){
	std::cout << "push piece" << std::endl;
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			if(piece[row][col] != NULL) {
				board->set(row +rowDeltaPiece, col +colDeltaPiece, piece[row][col]);
			} 
		}
	}
}

void
Block::pop(){
	std::cout << "pop piece" << std::endl;
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			if(piece[row][col] != NULL) {
				board->set(row +rowDeltaPiece, col +colDeltaPiece, NULL);
			} 
		}
	}
}

void
Block::debugBoard(){
	for(GLuint row = 0; row < board->Rows(); ++row) {
		for(GLuint col = 0; col < board->Cols(); ++col) {
			if(board->at(row,col) != NULL) {
				std::cout << '+';
			} else {
				std::cout << '-';
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
