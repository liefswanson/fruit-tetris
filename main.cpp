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

const GLuint WIDTH  = 540,
	         HEIGHT = 1040;


const GLuint COLUMNS  = 10,
	         ROWS     = 20;


const GLuint MARGINS = 20;

const GLfloat BG = 0.082f;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,
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

	chdir("shaders");

	GLuint vert     = readCompile("basic.vert",   GL_VERTEX_SHADER);
	
	//GLuint fApple   = readCompile("apple.frag",   GL_FRAGMENT_SHADER);
	//GLuint fBannana = readCompile("banana.frag",  GL_FRAGMENT_SHADER);
	//GLuint fGrape   = readCompile("grape.frag",   GL_FRAGMENT_SHADER);
	//GLuint fPear    = readCompile("pear.frag",    GL_FRAGMENT_SHADER);
	//GLuint fOrange  = readCompile("orange.frag",  GL_FRAGMENT_SHADER);
	//GLuint fDefault = readCompile("default.frag", GL_FRAGMENT_SHADER);

	GLuint fGrid    = readCompile("grid.frag",    GL_FRAGMENT_SHADER);


	//test.Relocate(-1.f, 1.f);
	
	glViewport(0, 0, WIDTH, HEIGHT);


	//board initialization

	GLfloat heightRatio = (GLfloat)HEIGHT / ((GLfloat)HEIGHT + (GLfloat)MARGINS*2);
	GLfloat widthRatio  = (GLfloat)WIDTH  / ((GLfloat)WIDTH  + (GLfloat)MARGINS*2);

	//take note that position can be negative and percent cannot 
	RangeMap xpos = RangeMap(0, 100, -widthRatio,  widthRatio);
	RangeMap ypos = RangeMap(0, 100, heightRatio, -heightRatio);
	RangeMap xpercent = RangeMap(0, 100, 0,  2*widthRatio);
	RangeMap ypercent = RangeMap(0, 100, 0,  2*heightRatio);

	Tile* board[COLUMNS][ROWS] = {};

	Tile* gridx[COLUMNS+1] = {};
	Tile* gridy[ROWS+1] = {};

	for(GLuint i = 0; i <= ROWS; i++) {
		gridy[i] =
			new Tile(xpos.map(0.f),
					 ypos.map(i*5.f),
					 xpercent.map(100.f),
					 ypercent.map(0.5f),
					 vert, fGrid,
					 NONE);
	}

	for(GLuint i = 0; i <= COLUMNS; i++) {
		gridx[i] =
			new Tile(xpos.map(i*10.f),
					 ypos.map(0.f),
					 xpercent.map(1.f),
					 ypercent.map(100.5f),
					 vert, fGrid,
					 NONE);
		std::cout << i << std::endl;
	}


	
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();

		glClearColor(BG, BG, BG, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for(GLuint i = 0; i <= COLUMNS; i++) {
			gridx[i]->Render();
		}
		
		for(GLuint i = 0; i <= ROWS; i++) {
		 	gridy[i]->Render();
		}
		
		glfwSwapBuffers(window);
	}

	for(GLuint i = 0; i <= COLUMNS; i++) {
		delete gridx[i];
	}
	
	for(GLuint i = 0; i <= ROWS; i++) {
	 	delete gridy[i];
	}
	

	glfwTerminate(); 
	return 0;
}
