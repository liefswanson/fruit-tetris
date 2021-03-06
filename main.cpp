#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unistd.h>

#include "tile.hpp"
#include "shader.hpp"
#include "rangeMap.hpp"
#include "board.hpp"
#include "block.hpp"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

using namespace std;

const double TIME_BETWEEN_DROPS = 0.5; 

const GLuint HEIGHT = 700,
	         WIDTH  = HEIGHT/2;

const GLfloat HW_RATIO = (GLfloat)HEIGHT/
	                     (GLfloat)WIDTH;

#define SPAWN_ROWS 5
#define ROWS       25
#define COLS       10

const GLuint MARGINS = 20;

const GLfloat BG = 0.082f;

const GLfloat PERCENT_INSIDE_MARGINS_HEIGHT = (GLfloat)HEIGHT / ((GLfloat)HEIGHT + 2*(GLfloat)MARGINS);
const GLfloat PERCENT_INSIDE_MARGINS_WIDTH  = (GLfloat)WIDTH  / ((GLfloat)WIDTH  + 2*(GLfloat)MARGINS);

//take note that position can be negative and percent cannot 
RangeMap xposition = RangeMap(0, 100, -PERCENT_INSIDE_MARGINS_WIDTH,      PERCENT_INSIDE_MARGINS_WIDTH);
RangeMap yposition = RangeMap(0, 100,  PERCENT_INSIDE_MARGINS_HEIGHT,    -PERCENT_INSIDE_MARGINS_HEIGHT);
RangeMap xpercent  = RangeMap(0, 100,  0,                             2 * PERCENT_INSIDE_MARGINS_WIDTH);
RangeMap ypercent  = RangeMap(0, 100,  0,                             2 * PERCENT_INSIDE_MARGINS_HEIGHT);

Board board (ROWS, COLS, SPAWN_ROWS, PERCENT_INSIDE_MARGINS_HEIGHT, PERCENT_INSIDE_MARGINS_WIDTH);
//needed because the callback for key events needs access
Block* globalBlock = NULL;


//-------------------------------------------------------------------------------------------------

class Grid {
private:
	Tile* gridx[COLS+1] = {};
	Tile* gridy[ROWS+1] = {};
	
public:
	Grid(GLuint vert, GLuint frag);
	~Grid();
	void Render();
};

//these magic numbers need fixing
Grid::Grid(GLuint vert, GLuint frag) {
	for (GLuint i = 0; i <= ROWS; i++) {
		gridy[i] = new Tile
			(xposition.map(0.f),  yposition.map(i * 10.f/HW_RATIO),
			 xpercent.map(100.f), ypercent.map(1.f/HW_RATIO),
			 vert, frag, NONE);
	}

	for (GLuint i = 0; i <= COLS; i++) {
		// need to apply extra length to compensate measurement scheme of tiles
		gridx[i] = new Tile
			(xposition.map(i * 10.f), yposition.map(0.f/HW_RATIO),
			 xpercent.map(1.f),       ypercent.map(100.f + 1.f/HW_RATIO), 
			 vert, frag, NONE);
	}
}

Grid::~Grid(){
	for (GLuint i = 0; i <= COLS; i++) {
		delete gridx[i];
	}
	
	for (GLuint i = 0; i <= ROWS; i++) {
	 	delete gridy[i];
	}
	
}

void
Grid::Render(){
	for (GLuint i = 0; i <= COLS; i++) {
		gridx[i]->Render();
	}
		
	for (GLuint i = 0; i <= ROWS; i++) {
		gridy[i]->Render();
	}
}

//-------------------------------------------------------------------------------------------------

GLboolean gameOver(){
	for(GLuint row = 0; row < SPAWN_ROWS; ++row ){
		for(GLuint col = 0; col < COLS; ++col ){
			if(board.at(row, col) != NULL) {
				std::cout << "Game Over" << std::endl;
				return GL_TRUE;
			}
		}	
	}
	return GL_FALSE;
}

void reset() {
	board.clear();
	globalBlock->makeBlock();
}

//-------------------------------------------------------------------------------------------------

void
moveBlockDown(){
	if(globalBlock->canMoveD()) {
		globalBlock->applyMove();	
	} else {
		if (gameOver()) {
			reset();
			return;
		}
		globalBlock->makeBlock();
		// diff is pointer to array on heap
		auto needsRemoval = GL_TRUE;
		while (needsRemoval) {
			auto a = board.ScanForFullRows();
			auto b = board.ScanForFruitChainsRows();
			auto c = board.ScanForFruitChainsCols();

            //board.debugDiff(a);
			//board.debugDiff(b);
			//board.debugDiff(c);

			auto temp = board.MergeDiffs(a,    b);
			auto diff = board.MergeDiffs(temp, c);
			board.RemoveDiff(diff);
			board.debugDiff(diff);

			needsRemoval = board.validateDiff(diff);

			delete[] diff;
			delete[] temp;

			delete[] a;
			delete[] b;
			delete[] c;
		}
		
//board.RemoveDiff(diff);
	}
}

void
moveBlockRight(){
	if(globalBlock->canMoveR()) {
		globalBlock->applyMove();	
	} else {
		globalBlock->discardMove();	
	}
}

void
moveBlockLeft(){
	if(globalBlock->canMoveL()) {
		globalBlock->applyMove();	
	} else {
		globalBlock->discardMove();	
	}
}

void
rotateBlock(GLint modifier) {
	if(modifier == GLFW_MOD_SHIFT) {
		if(globalBlock->canRotC()) {
			globalBlock->applyMove();	
		} else {
			globalBlock->discardMove();	
		}
	} else {
		if(globalBlock->canRotW()) {
			globalBlock->applyMove();	
		} else {
			globalBlock->discardMove();	
		}	
	}
	
}

void
shuffleBlock(GLint modifier) {
	if(modifier == GLFW_MOD_SHIFT) {
		globalBlock->shuffleL();
	} else {
		globalBlock->shuffleR();
	}
}

void
key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods) {
	if (action == GLFW_PRESS ||
		action == GLFW_REPEAT) {
		switch(key) {
		case GLFW_KEY_R:
			reset();
			break;
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_RIGHT:
			moveBlockRight();
			break;
		case GLFW_KEY_LEFT:
			moveBlockLeft();
			break;
		case GLFW_KEY_DOWN:
			moveBlockDown();
			break;
		case GLFW_KEY_UP:
			rotateBlock(mods);
			break;
		case GLFW_KEY_SPACE:
			shuffleBlock(mods);
			break;
		}
	}
}


//-------------------------------------------------------------------------------------------------

int
main(int argc, char *argv[]) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH + 2*MARGINS, HEIGHT + 2*MARGINS,
										  "fruit tetris - Lief Swanson",
										  nullptr, nullptr);
	glfwMakeContextCurrent(window);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	
	glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
    }

	glfwSetKeyCallback(window, key_callback);
	
	GLuint vBasic  = readCompile("shaders/basic.vert",   GL_VERTEX_SHADER);
	
	GLuint frags[6];
	frags[NONE]    = NONE;
	frags[APPLE]   = readCompile("shaders/apple.frag",   GL_FRAGMENT_SHADER);
	frags[BANANA]  = readCompile("shaders/banana.frag",  GL_FRAGMENT_SHADER);
	frags[GRAPE]   = readCompile("shaders/grape.frag",   GL_FRAGMENT_SHADER);
	frags[PEAR]    = readCompile("shaders/pear.frag",    GL_FRAGMENT_SHADER);
	frags[ORANGE]  = readCompile("shaders/orange.frag",  GL_FRAGMENT_SHADER);

	GLuint fGrid   = readCompile("shaders/grid.frag",    GL_FRAGMENT_SHADER);

	glViewport(0, 0, WIDTH + 2*MARGINS, HEIGHT + 2*MARGINS);

	Grid grid (vBasic, fGrid);
	Block block(&board, frags, vBasic);
	globalBlock = &block;

	block.makeBlock();

	double timeSinceLastDrop  = 0;
	
	while (!glfwWindowShouldClose(window)){
		glfwPollEvents();

		glClearColor(BG, BG, BG, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		
		if(glfwGetTime() -timeSinceLastDrop > TIME_BETWEEN_DROPS ){
			moveBlockDown();
			timeSinceLastDrop = glfwGetTime();
		}
		
		board.Render();
		grid.Render();
		
		glfwSwapBuffers(window);
		//sleep(1);
	}

	glfwTerminate(); 
	return 0;
}

