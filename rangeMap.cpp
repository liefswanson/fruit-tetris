#include "rangeMap.hpp"


GLfloat
mapTo(GLfloat inLow,  GLfloat inHigh,
	  GLfloat outLow, GLfloat outHigh,
	  GLfloat x) {

	GLfloat inRange = inHigh-inLow;
	GLfloat outRange = outHigh-outLow;

	GLfloat xOut = (x - inLow) * (outRange / inRange) + outLow;
	
	return xOut;
}
