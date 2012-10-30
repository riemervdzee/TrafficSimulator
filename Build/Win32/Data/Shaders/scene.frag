#version 330

in vec2 lmCoord;
in vec2 texCoord;

uniform sampler2D tex;
out vec4 fragcolor;

void main()
{
	fragcolor = texture(tex, texCoord);
}