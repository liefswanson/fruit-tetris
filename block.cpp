#include "block.hpp"

Block::Block(Board* board, GLuint frags[], GLuint vert){
	srand(time(NULL));
	this->board = board;
	this->vert = vert;
	for(GLuint i = 0; i < FRUITS; ++i) {
		this->frags[i] = frags[i];
	}
}

Block::~Block(){
}

void
Block::applyMove() {
	pop();
	// debugBoard();
	syncPiece();
	push();
	// debugBoard();
}

void
Block::discardMove(){
	syncCheck();
}

GLboolean
Block::checkMove() {
	GLboolean temp = GL_TRUE;
	pop();
	// debugBoard();
	
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			if(check[row][col] != NULL){
				if(!board->on(row +rowDeltaCheck, col +colDeltaCheck) ||
				    board->at(row +rowDeltaCheck, col +colDeltaCheck) != NULL){
					temp = GL_FALSE;
				}
			}
		}
	}
	push();
	// debugBoard();
	
	// if(temp) {
	// 	std::cout << "legal move" << std::endl;
	// } else {
	// 	std::cout << "illegal move" << std::endl;
	// }
	return temp;
}


GLboolean
Block::canRotW(){
	if (shape == I_piece ||
		shape == S_piece) {
		if (rotation == 0) {
			rotation = 1;
		} else if (rotation == 1) {
			rotation = 0;
			for(GLuint row = 0; row < PIECE_SIZE; ++row) {
				for(GLuint col = 0; col < PIECE_SIZE; ++col) {
					check[row][col] = piece[PIECE_SIZE -1 -col][row];
				}
			}
			return checkMove();
		}
	}
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[col][PIECE_SIZE -1 -row];
		}
	}
	return checkMove();
}

GLboolean
Block::canRotC(){
	if (shape == I_piece ||
		shape == S_piece) {
		if (rotation == 0) {
			rotation = 1;
			for(GLuint row = 0; row < PIECE_SIZE; ++row) {
				for(GLuint col = 0; col < PIECE_SIZE; ++col) {
					check[row][col] = piece[col][PIECE_SIZE -1 -row];
				}
			}
			return checkMove();
		} else if (rotation == 1) {
			rotation = 0;
		}
	} else {
		if (rotation < 4) {
			++rotation;
		} else {
			rotation = 0;
		}
	}
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

void
Block::shuffleL() {
	//uses a single bubble ->
	for(GLuint i = 0; i < TILES_PER_BLOCK-1; ++i) {
		std::swap(*orderPiece[i], *orderPiece[i +1]);
	}
	syncCheck();
}

void
Block::shuffleR(){
	//uses a single bubble <-
	for(GLuint i = TILES_PER_BLOCK-1; i > 0 ; --i) {
	 	std::swap(*orderPiece[i],*orderPiece[i -1]);
	}
	syncCheck();
}

//-------------------------------------------------------------------------------------------------

void
Block::makeBlock(){
	this->clear();
	shape    = rand() % SHAPES;
	rotation = 0;
	switch(shape) {
	case I_piece:
		// std::cout << 'I' << std::endl;
		makeI();
		break;
	case L_piece:
		// std::cout << 'L' << std::endl;
		makeL();
		break;
	case S_piece:
		// rystd::cout << 'S' << std::endl;
		makeS();
		break;
	}

	syncCheck();
	
	GLuint rotations = rand() % 4;
	// std::cout << rotations  << " rotations on new block" << std::endl;
	for(GLuint i = 0; i < rotations; ++i) {
		canRotW();
		applyMove();
	}
}

void
Block::spawnTile(GLuint row, GLuint col, GLuint order) {
	GLuint fruit;
	fruit = randFruit();
	//fruit = ORANGE;
	piece[row][col] = board->makeAt(row +rowDeltaPiece,
									col +colDeltaPiece,
									vert, frags[fruit], fruit);
	orderPiece[order] = piece[row][col];
}

void
Block::makeI(){
    //
	//
	// ++++
	//
	//
    //2, 0..3

	spawnTile(2, 0, 0);
	spawnTile(2, 1, 1);
	spawnTile(2, 2, 2);
	spawnTile(2, 3, 3);
}


void
Block::makeL(){
	//
	//
	// +++
	// +
	//
    //3, 1
	//2, 1..3
	
	spawnTile(3, 1, 0);
	spawnTile(2, 1, 1);
	spawnTile(2, 2, 2);
	spawnTile(2, 3, 3);
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

	spawnTile(3, 1, 0);
	spawnTile(3, 2, 1);
	spawnTile(2, 2, 2);
	spawnTile(2, 3, 3);
}

GLuint
Block::randFruit(){
	return (rand() % (FRUITS -1)) +1;
}

//-------------------------------------------------------------------------------------------------


void
Block::clear(){
	// for testing so i can see the block
	// rowDeltaPiece = 10;
	rowDeltaPiece = 0;
	colDeltaPiece = rand() % (board->Cols() -PIECE_SIZE -1);
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			piece[row][col] = NULL;
		}
	}

	for(GLuint i = 0; i < TILES_PER_BLOCK; ++i) {
		orderPiece[i] = NULL;
	}

	syncCheck();
}

void
Block::syncPiece(){
	// std::cout << "sync piece" << std::endl;
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			piece[row][col] = check[row][col];
		}
	}

	for(GLuint i = 0; i < TILES_PER_BLOCK; ++i) {
		orderPiece[i] = orderCheck[i];
	}
	
	rowDeltaPiece = rowDeltaCheck;
	colDeltaPiece = colDeltaCheck;
}

void
Block::syncCheck(){
	// std::cout << "sync check" << std::endl;
	for(GLuint row = 0; row < PIECE_SIZE; ++row) {
		for(GLuint col = 0; col < PIECE_SIZE; ++col) {
			check[row][col] = piece[row][col] ;
		}
	}

	for(GLuint i = 0; i < TILES_PER_BLOCK; ++i) {
		orderCheck[i] = orderPiece[i];
	}
	
	rowDeltaCheck = rowDeltaPiece;
	colDeltaCheck = colDeltaPiece;
}

void
Block::push(){
	// std::cout << "push piece" << std::endl;
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
	// std::cout << "pop piece" << std::endl;
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
