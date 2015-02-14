#include "block.hpp"

GLuint
Block::indices[] = {
	0, 1, 3,
	1, 2, 3
};

Block::Block(GLfloat x, GLfloat y,
			 GLfloat w, GLfloat h,
			 GLuint vert, GLuint frag,
			 GLuint fruit){
    this->w = w;
	this->h = h;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	GLfloat vertices[] = {
		w,    0.f,  0.f, // tr
		w,   -h,    0.f, // br
		0.f, -h,    0.f, // bl
		0.f,  0.f,  0.f  // tl
	};

	Shader shader = Shader();
	shader.Attach(vert);
	shader.Attach(frag);
	shader.Link();

	_fruit = fruit;
	
	//bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); // attach vbo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW); // attach ebo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // how vao interprets vertices array
	glEnableVertexAttribArray(0);
	
	//unbind
	glBindVertexArray(UNBIND);
	glBindBuffer(GL_ARRAY_BUFFER, UNBIND);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UNBIND);	
}

Block::~Block(){}

void
Block::Relocate(GLfloat x, GLfloat y) {
	shader.Use();
	GLint vertPos = glGetUniformLocation(shader.ref(), "position");
	glUniform2f(vertPos, x, y);
}

void
Block::Render() {
	shader.Use();
	GLint vertPos = glGetUniformLocation(shader.ref(), "position");
	glUniform2f(vertPos, -1.f, -1.f);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(UNBIND);
}
