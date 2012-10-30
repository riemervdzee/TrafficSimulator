#version 330

in vec2 lmCoord;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D lm;

out vec4 fragcolor;

void main()
{
	fragcolor = texture(tex, texCoord) * texture(lm, lmCoord);
}