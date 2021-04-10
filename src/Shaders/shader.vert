#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;

const int MAX_LIGHTS = 5;

out vec3 pass_pos;
out vec3 pass_color;
out vec3 pass_normal;
out vec2 pass_uv;
out vec4 fragPosLightSpace[MAX_LIGHTS];

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

struct Light {
	mat4 lightSpace;
	float innerCutoff;
	float outerCutoff;
	vec3 color;
	vec3 pos;
	vec3 dir;
	sampler2D shadowMap;
};

uniform Light lights[MAX_LIGHTS];
uniform int num_lights;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0);

	pass_pos = (model * vec4(pos, 1.0)).xyz;
	pass_normal = (model * vec4(normal, 0)).xyz;
	pass_uv = uv;
	pass_color = color;

	for (int i = 0; i < num_lights; i++) {
		fragPosLightSpace[i] = lights[i].lightSpace * vec4(pass_pos, 1.0);
	}

}