//#version 330

// input vertex attributes
#if __VERSION__ >= 330
layout(location=0) in vec3 inPos;
layout(location=1) in vec3 inCol;
#else
in vec3 inPos;
in vec3 inCol;
#endif

out vec3 color;

// uniform data
uniform mat4 mvpMatrix;

void main()
{
	color = inCol;
	gl_Position = mvpMatrix * vec4(inPos, 1.0);
}
