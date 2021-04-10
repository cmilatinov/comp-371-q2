#version 330

const int MAX_LIGHTS = 5;
const float AMBIENT_LIGHT = 0.2;

in vec3 pass_pos;
in vec3 pass_color;
in vec3 pass_normal;
in vec2 pass_uv;
in vec4 fragPosLightSpace[MAX_LIGHTS];

out vec4 colour;

struct Light {
	mat4 lightSpace;
	float innerCutoff;
	float outerCutoff;
	vec3 color;
	vec3 pos;
	vec3 dir;
	sampler2D shadowMap;
};

struct Material {
	float specular_intensity;
	float shininess;
};

uniform Material material;
uniform vec3 eye_position;
uniform bool shadow_toggle = true;
uniform bool use_texture = true;
uniform bool use_lighting = true;
uniform sampler2D tex;

uniform Light lights[MAX_LIGHTS];
uniform int num_lights;

float shadowCalculation(vec4 fragPos, sampler2D shadowMap, vec3 normal, vec3 lightDir) {
	if (!shadow_toggle)
		return 1.0f;

	vec3 projCoords = fragPos.xyz / fragPos.w;
	projCoords = projCoords * 0.5 + 0.5;

	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	float bias = max(0.003 * (1.0 - dot(normal, lightDir)), 0.0003);
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	const int kernelSize = 3;
	for(int x = -(kernelSize - 1) / 2; x <= 1; x++) {
		for(int y = -(kernelSize - 1) / 2; y <= 1; y++) {
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	return 1.0 - (shadow / (kernelSize * kernelSize));
}

void main()
{
	// Use texture / color depending on what is needed
	vec3 color = use_texture ? texture(tex, pass_uv).rgb : pass_color;

	// Don't compute lighting if not needed (axis lines, grid)
	if (!use_lighting) {
		colour = vec4(color, 1.0);
		return;
	}

	// Lighting calculations
	vec3 lighting = color * AMBIENT_LIGHT;
	for (int i = 0; i < num_lights; i++) {
		vec3 normal = normalize(pass_normal);
		vec3 lightDir = normalize(lights[i].pos - pass_pos);

		// Check that fragment is in spotlight cone
		float theta = dot(lightDir, normalize(-lights[i].dir));
		float epsilon = lights[i].innerCutoff - lights[i].outerCutoff;
		float intensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);
		if (theta > lights[i].outerCutoff) {
			float diffuse = max(dot(normal, lightDir), 0.0);
			vec3 viewDir = normalize(eye_position - pass_pos);
			vec3 reflectDir = reflect(-lightDir, normal);
			float specular = material.specular_intensity * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			float shadow = shadowCalculation(fragPosLightSpace[i], lights[i].shadowMap, normal, lightDir);

			lighting += (diffuse + specular) * intensity * shadow * lights[i].color * color;
		}
	}

	colour = vec4(lighting, 1.0);
}