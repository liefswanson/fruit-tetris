#include <iostream>
#include <fstream>
#include <unistd.h>

#include "tile.hpp"
#include "shader.hpp"
#include "rangeMap.hpp"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

using namespace std;

const GLuint HEIGHT = 1000,
	         WIDTH  = 500;

const GLfloat HW_RATIO = (GLfloat)HEIGHT/
	                     (GLfloat)WIDTH;

#define SPAWN_ROWS 4
#define ROWS       20
#define COLS       10

const GLuint MARGINS = 20;

const GLfloat BG = 0.082f;

const GLfloat PERCENT_INSIDE_MARGINS_HEIGHT = (GLfloat)HEIGHT / ((GLfloat)HEIGHT + (GLfloat)MARGINS*2);
const GLfloat PERCENT_INSIDE_MARGINS_WIDTH  = (GLfloat)WIDTH  / ((GLfloat)WIDTH  + (GLfloat)MARGINS*2);

//take note that position can be negative and percent cannot 
RangeMap xposition = RangeMap(0, 100, -PERCENT_INSIDE_MARGINS_WIDTH,      PERCENT_INSIDE_MARGINS_WIDTH);
RangeMap yposition = RangeMap(0, 100,  PERCENT_INSIDE_MARGINS_HEIGHT,    -PERCENT_INSIDE_MARGINS_HEIGHT);
RangeMap xpercent  = RangeMap(0, 100,  0,                             2 * PERCENT_INSIDE_MARGINS_WIDTH);
RangeMap ypercent  = RangeMap(0, 100,  0,                             2 * PERCENT_INSIDE_MARGINS_HEIGHT);


Tile* spawn[COLS][SPAWN_ROWS] = {};
Tile* board[COLS][ROWS]       = {};

class Grid {
private:
	Quad* gridx[COLS+1] = {};
	Quad* gridy[ROWS+1] = {};
	
public:
	Grid(GLuint vert, GLuint frag);
	~Grid();
	void render();
};

//these magic numbers need fixing
Grid::Grid(GLuint vert, GLuint frag) {
	for (GLuint i = 0; i <= ROWS; i++) {
		gridy[i] = new Quad
			(xposition.map(0.f),  yposition.map(i * 10.f/HW_RATIO),
			 xpercent.map(100.f), ypercent.map(1.f/HW_RATIO),
			 vert, frag);
	}

	for (GLuint i = 0; i <= COLS; i++) {
		gridx[i] = new Quad
			(xposition.map(i * 10.f), yposition.map(0.f/HW_RATIO),
			 xpercent.map(1.f),       ypercent.map(100.f + 1.f/HW_RATIO), // need to apply extra length to compensate measurement scheme of tile
			 vert, frag);
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
Grid::render(){
	for (GLuint i = 0; i <= COLS; i++) {
		gridx[i]->Render();
	}
		
	for (GLuint i = 0; i <= ROWS; i++) {
		gridy[i]->Render();
	}
}

//-------------------------------------------------------------------------------------------------

int
main() {
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

	GLuint vBasic   = readCompile("shaders/basic.vert",   GL_VERTEX_SHADER);
	
	//GLuint fApple   = readCompile("shaders/apple.frag",   GL_FRAGMENT_SHADER);
	//GLuint fBannana = readCompile("shaders/banana.frag",  GL_FRAGMENT_SHADER);
	//GLuint fGrape   = readCompile("shaders/grape.frag",   GL_FRAGMENT_SHADER);
	//GLuint fPear    = readCompile("shaders/pear.frag",    GL_FRAGMENT_SHADER);
	//GLuint fOrange  = readCompile("shaders/orange.frag",  GL_FRAGMENT_SHADER);

	GLuint fGrid    = readCompile("shaders/grid.frag",    GL_FRAGMENT_SHADER);


	//test.Relocate(-1.f, 1.f);
	
	glViewport(0, 0, WIDTH + 2*MARGINS, HEIGHT + 2*MARGINS);

	Grid grid = Grid(vBasic, fGrid);

	while (!glfwWindowShouldClose(window)){
		glfwPollEvents();

		glClearColor(BG, BG, BG, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		grid.render();
		
		glfwSwapBuffers(window);
	}

	glfwTerminate(); 
	return 0;
}

