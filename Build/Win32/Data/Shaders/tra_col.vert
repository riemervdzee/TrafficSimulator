#version 330

// input vertex attributes
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inDiffuse;

// output data
out vec3 diffuse;

// uniform data
uniform mat4 mvpMatrix;

void main()
{
	gl_Position = mvpMatrix * vec4(inPos, 1.0);
	diffuse = inDiffuse;
}