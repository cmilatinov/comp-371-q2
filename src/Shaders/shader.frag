#version 330

in vec3 pass_pos;
in vec3 pass_color;
in vec3 pass_normal;
in vec2 pass_uv;

out vec4 colour;

struct Light
{
	vec3 color;
	float ambient_intensity;
	float diffuse_intensity;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

// Specular lighting
struct Material
{
	float specular_intensity;
	float shininess;
};

struct OmniShadowMap
{
	samplerCube shadow_map;
	float far_plane;
};

uniform int point_light_count;

uniform PointLight point_light;

uniform Material material;
// Camera position
uniform vec3 eye_position;

uniform bool shadow_toggle = true;

uniform OmniShadowMap omni_shadow_map;

uniform bool use_texture = true;
uniform bool use_lighting = true;
uniform sampler2D tex;

vec3 gridSamplingDisk[20] = vec3[]
(
	vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
	vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
	vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
	vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
	vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 fragPos)
{
	// get vector between fragment position and light position

	vec3 fragToLight = fragPos - point_light.position;

	float currentDepth = length(fragToLight);

	float shadow = 0.0;
	float bias = 0.15;
	int samples = 20;
	float viewDistance = length(eye_position - fragPos);
	float diskRadius = (1.0 + (viewDistance / omni_shadow_map.far_plane)) / 25.0;

	for(int i = 0; i < samples; ++i)
	{
		float closestDepth = texture(omni_shadow_map.shadow_map, fragToLight + gridSamplingDisk[i] * diskRadius).r;
		closestDepth *= omni_shadow_map.far_plane;   // undo mapping [0;1]
		if(currentDepth - bias > closestDepth)
		shadow += 1.0;
	}
	shadow /= float(samples);

	return shadow;
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

	vec3 normal = normalize(pass_normal);

	// ambient
	vec3 ambient = 0.3 * color;

	// diffuse
	vec3 lightDir = normalize(point_light.position - pass_pos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * point_light.base.color;

	// specular
	vec3 viewDir = normalize(eye_position - pass_pos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
	vec3 specular = spec * point_light.base.color;

	// calculate shadow
	float shadow = shadow_toggle ? ShadowCalculation(pass_pos) : 0.0;
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

	colour = vec4(lighting, 1.0);
}