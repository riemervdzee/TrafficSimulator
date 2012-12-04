// input vertex attributes
in vec3 inPos;
in vec3 inCol;
out vec3 color;

// uniform data
uniform mat4 mvpMatrix;

void main()
{
	color = inCol;
	gl_Position = mvpMatrix * vec4(inPos, 1.0);
}
