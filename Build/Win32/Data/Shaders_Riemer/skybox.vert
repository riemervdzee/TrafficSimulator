in vec3 inPos;
out vec3 UV;
uniform mat4 projView;

void main()
{
	gl_Position = (projView * vec4(inPos, 1.0)).xyww;
	UV = inPos;
}