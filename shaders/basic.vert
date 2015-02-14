#version 330 core

layout (location = 0) in vec2 dimension;

uniform vec2 position;

void main(){
	gl_Position = vec4(position.xy + dimension.xy, 0.0f, 1.0f);
}
 
