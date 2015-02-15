#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <GL/glew.h>

// class RangeMap {

// private:
// 	GLfloat inLow,  inHigh;
// 	GLfloat outLow, outHigh;
	
// public:
// 	RangeMap(GLfloat inLow,  GLfloat inHigh,
// 			 GLfloat outLow, GLfloat outHigh);
	
// 	GLfloat
// 	map(GLfloat x);
// };

	GLfloat
	mapTo(GLfloat inLow,  GLfloat inHigh,
		GLfloat outLow, GLfloat outHigh,
		GLfloat x);

#endif // __MAP_HPP__
