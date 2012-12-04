in vec3 UV;
out vec4 fragcolor;
uniform samplerCube cubeMap;

void main()
{
	fragcolor = texture(cubeMap, UV);
}