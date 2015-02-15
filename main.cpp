#include <iostream>
#include <fstream>
#include <unistd.h>

#include "tile.hpp"
#include "shader.hpp"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

using namespace std;

const GLuint WIDTH  = 800,
	         HEIGHT = 800;

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
	//GLuint fBannana = readCompile("banana.frag", GL_FRAGMENT_SHADER);
	//GLuint fGrape   = readCompile("grape.frag",   GL_FRAGMENT_SHADER);
	GLuint fPear    = readCompile("pear.frag",    GL_FRAGMENT_SHADER);
	//GLuint fOrange  = readCompile("orange.frag",  GL_FRAGMENT_SHADER);
	//GLuint fDefault = readCompile("default.frag", GL_FRAGMENT_SHADER);

	//GLuint fGrid    = readCompile("grid.frag",    GL_FRAGMENT_SHADER);


	Tile test = Tile(0.f, 0.f,
					   0.4f, 0.4f,
					   vert, fPear,
					   PEAR);
	//test.Relocate(-1.f, -1.f);
	
	glViewport(0, 0, WIDTH, HEIGHT);

	test.Relocate(-1.f, 1.f);

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();

		glClearColor(BG, BG, BG, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		test.Render();
		
		glfwSwapBuffers(window);
	}

	glfwTerminate(); 
	return 0;
}
