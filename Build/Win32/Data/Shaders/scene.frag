#version 330

in vec2 lmCoord;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D lm;

out vec4 fragcolor;

void main()
{
	vec4 color = texture(tex, texCoord) * texture(lm, lmCoord);
	fragcolor = color * 1.8;
}