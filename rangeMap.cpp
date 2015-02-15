#include "rangeMap.hpp"


RangeMap::RangeMap(GLfloat inLow,  GLfloat inHigh,
				   GLfloat outLow, GLfloat outHigh){
	this->inOffset  = inLow;
	this->outOffset = outLow;

	GLfloat inRange   = inHigh  - inLow;
	GLfloat outRange  = outHigh - outLow;

	this->ratio = outRange / inRange;
}

GLfloat
RangeMap::map(GLfloat x){
	return (x - inOffset) * ratio + outOffset;
}

RangeMap::~RangeMap(){}

GLfloat
mapTo(GLfloat inLow,  GLfloat inHigh,
	  GLfloat outLow, GLfloat outHigh,
	  GLfloat x) {

	GLfloat inRange = inHigh-inLow;
	GLfloat outRange = outHigh-outLow;

	GLfloat xOut = (x - inLow) * (outRange / inRange) + outLow;
	
	return xOut;
}
