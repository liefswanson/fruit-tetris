#version 330 core

layout (location = 0) in vec3 dimension;

uniform vec2 position = vec2 (0.0f, 0.0f);

void main(){
	gl_Position = vec4(position.xy + dimension.xy, 0.0f, 1.0f);
}
