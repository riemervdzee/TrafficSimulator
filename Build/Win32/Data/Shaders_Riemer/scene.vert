// input vertex attributes
in vec3 inPos;
in vec2 inTexCoord;
in vec2 inLmCoord;

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
