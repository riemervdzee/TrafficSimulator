#version 330

// input vertex attributes
layout(location=0) in vec3 inPos;
layout(location=1) in vec2 inTexCoord;
layout(location=2) in vec2 inLmCoord;

// output data
out vec2 lmCoord;
out vec2 texCoord;

// uniform data
uniform mat4 mvpMatrix;

void main()
{
	gl_Position = mvpMatrix * vec4(inPos, 1.0);
	lmCoord = inLmCoord;
	texCoord = inTexCoord;
}
