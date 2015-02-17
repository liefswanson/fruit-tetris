#include <iostream>
#include <fstream>
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

const GLuint HEIGHT = 700,
	         WIDTH  = HEIGHT/2;

const GLfloat HW_RATIO = (GLfloat)HEIGHT/
	                     (GLfloat)WIDTH;

#define SPAWN_ROWS 5
#define ROWS       20
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

Board board (ROWS, COLS, SPAWN_ROWS, PERCENT_INSIDE_MARGINS_HEIGHT, PERCENT_INSIDE_MARGINS_WIDTH, HW_RATIO);

//needed because the callback for key events needs access
Block* globalBlock = NULL;

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
		gridx[i] = new Tile
			(xposition.map(i * 10.f), yposition.map(0.f/HW_RATIO),
			 xpercent.map(1.f),       ypercent.map(100.f + 1.f/HW_RATIO), // need to apply extra length to compensate measurement scheme of tile
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


void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    std::cout << key << std::endl;
	if (action == GLFW_PRESS) {
		switch(key){
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_RIGHT:
			if(globalBlock->canMoveR() == GL_TRUE) {
				globalBlock->applyMove();	
			}
			break;
		case GLFW_KEY_LEFT:
			if(globalBlock->canMoveL() == GL_TRUE){
				globalBlock->applyMove();
			}
			break;
		case GLFW_KEY_DOWN:
			if(globalBlock->canRotW() == GL_TRUE) {
				globalBlock->applyMove();
			}
			break;
		case GLFW_KEY_UP:
			if(globalBlock->canRotC() == GL_TRUE) {
				globalBlock->applyMove();
			}
			break;
		case GLFW_KEY_SPACE:
			if(globalBlock->canMoveD() == GL_TRUE) {
				globalBlock->applyMove();
			}
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

	GLuint vBasic   = readCompile("shaders/basic.vert",   GL_VERTEX_SHADER);
	
	GLuint frags[6];
	frags[NONE]    = NONE;
	frags[APPLE]   = readCompile("shaders/apple.frag",   GL_FRAGMENT_SHADER);
	frags[BANANA]  = readCompile("shaders/banana.frag",  GL_FRAGMENT_SHADER);
	frags[GRAPE]   = readCompile("shaders/grape.frag",   GL_FRAGMENT_SHADER);
	frags[PEAR]    = readCompile("shaders/pear.frag",    GL_FRAGMENT_SHADER);
	frags[ORANGE]  = readCompile("shaders/orange.frag",  GL_FRAGMENT_SHADER);

	GLuint fGrid    = readCompile("shaders/grid.frag",    GL_FRAGMENT_SHADER);

	glViewport(0, 0, WIDTH + 2*MARGINS, HEIGHT + 2*MARGINS);

	Grid grid (vBasic, fGrid);
	Board* temp = &board;
	Block block(temp, frags, vBasic);
	globalBlock = &block;

	block.makeBlock();
	while (!glfwWindowShouldClose(window)){
		glfwPollEvents();

		glClearColor(BG, BG, BG, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		board.Render();
		grid.Render();
		
		glfwSwapBuffers(window);
		//usleep(100);
	}

	glfwTerminate(); 
	return 0;
}

