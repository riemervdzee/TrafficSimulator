#version 330

in vec2 lmCoord;
in vec2 texCoord;
in vec3 diffuse;

uniform sampler2D lightmap;
uniform sampler2D texture;

out vec4 fragcolor;

void main()
{
	fragcolor = vec4(diffuse, 1.0);//texture(lightmap, lmCoord) * texture(texture, texCoord);
}