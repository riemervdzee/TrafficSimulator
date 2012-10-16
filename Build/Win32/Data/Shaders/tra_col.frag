#version 330

in vec3 diffuse
out vec4 fragcolor;

void main()
{
	fragcolor = vec4(diffuse, 1.0);
}