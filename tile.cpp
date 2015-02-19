#include "tile.hpp"

GLuint
Tile::indices[] = {
	0, 1, 3,
	1, 2, 3
};

Tile::Tile(GLfloat x, GLfloat y,
		   GLfloat w, GLfloat h,
		   GLuint vert, GLuint frag,
		   GLuint fruit){
	
	shader = glCreateProgram();
	glAttachShader(shader, vert);
	glAttachShader(shader, frag);

	glLinkProgram(shader);
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDetachShader(shader, vert);
	glDetachShader(shader, frag);

	GLfloat vertices[] = {
		w,    0.f,  // tr
		w,   -h,    // br
		0.f, -h,    // bl
		0.f,  0.f   // tl
	};

	//initialize
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // attach vbo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // attach ebo
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0); // how vao interprets vertices array
	glEnableVertexAttribArray(0);

	//unbind
	glBindVertexArray(UNBIND);
	glBindBuffer(GL_ARRAY_BUFFER, UNBIND);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UNBIND);	

    this->w = w;
	this->h = h;

	Relocate(x, y);
	_fruit = fruit;
}

Tile::Tile(const Tile& that){
	this->w = that.w;
	this->h = that.h;

	this->VAO = that.VAO;
	this->VBO = that.VBO;
	this->EBO = that.EBO;

	this->shader = that.shader;
	_fruit = that._fruit;
}

Tile::~Tile(){
	glDeleteProgram(shader);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void
Tile::Relocate(GLfloat x, GLfloat y) {
	glUseProgram(shader);
	GLint vertPos = glGetUniformLocation(shader, "position");
	glUniform2f(vertPos, x, y);
}

void
Tile::Render() {
	glUseProgram(shader);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(UNBIND);
}

GLuint
Tile::fruit(){return _fruit;}
