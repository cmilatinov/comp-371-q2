#version 330

in vec3 vCol;

out vec4 colour;

void main()
{
	colour = vec4(vCol.r, vCol.g, vCol.b, 1.0f);
}