#version 330

in vec2 lmCoord;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D lm;

out vec4 fragcolor;

vec4 dirColor = vec4(254/255.0, 252/255.0, 205/255.0, 1.0);
vec4 ambColor = vec4(64.0/255.0, 64.0/255.0, 64.0/255.0, 1.0);

void main()
{
	//vec4 src = texture(tex, texCoord);
	//vec4 dst = texture(lm, lmCoord) * ambColor;
	vec4 color = texture(tex, texCoord) * (texture(lm, lmCoord)  + ambColor * dirColor);
	//vec4 color = (src + dst) - (src * dst);
	fragcolor = color;
}
