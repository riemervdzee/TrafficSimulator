#version 330

// input vertex attributes
layout(location = 0) in vec3 inPos;

// uniform data
uniform mat4 mvpMatrix;

void main()
{
	//gl_PointSize = 128.0;
	gl_Position = mvpMatrix * vec4(inPos, 1.0);
}