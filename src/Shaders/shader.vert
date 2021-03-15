#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 norm;

out vec3 vCol;
out vec3 normal;
out vec3 fragment_position;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vCol = aColor;

	// Ensure we only apply calculations to rotations made on the normals
	normal = mat3(transpose(inverse(model))) * norm;

	fragment_position = (model * vec4(pos, 1.0)).xyz;
}