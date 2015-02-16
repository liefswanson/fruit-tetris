#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <GL/glew.h>

class RangeMap {

	// internals determining how mapping from one range to another is done
	// linear mapping
	// in practise this is used to map from numbers in a 100 percent range to the normalized grid in opengl
private:
	GLfloat inOffset, outOffset;
	GLfloat ratio;

	// creates a new mapping
public:
	RangeMap(GLfloat inLow,  GLfloat inHigh,
			 GLfloat outLow, GLfloat outHigh);
	~RangeMap();

	// moves a number from one map to another
	GLfloat
	map(GLfloat x);
};

//testing function used for the same purpose as the class but must specify ranges on each use
GLfloat
mapTo(GLfloat inLow,  GLfloat inHigh,
	  GLfloat outLow, GLfloat outHigh,
	  GLfloat x);

#endif // __MAP_HPP__
