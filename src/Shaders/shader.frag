#version 330

in vec3 vCol;
in vec3 normal;
in vec3 fragment_position;

out vec4 colour;

const int MAX_POINT_LIGHTS = 3;

struct Light
{
	vec3 color;
	float ambient_intensity;
	float diffuse_intensity;
};

struct DirectionalLight
{
	Light base;
	vec3 direction;
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

uniform DirectionalLight directional_light;
uniform PointLight point_lights[MAX_POINT_LIGHTS];

uniform Material material;
// Camera position
uniform vec3 eye_position;

uniform OmniShadowMap omni_shadow_maps[MAX_POINT_LIGHTS];

vec3 gridSamplingDisk[20] = vec3[]
(
vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

vec4 calculate_light_by_direction(Light light, vec3 direction, float shadow_factor)
{
	vec4 ambient_color = vec4(light.color, 1.0f) * light.ambient_intensity;

	float diffuse_factor = max(dot(normalize(normal), normalize(direction)), 0.0f);
	vec4 diffuse_color = vec4(light.color * light.diffuse_intensity * diffuse_factor, 1.0f);

	vec4 specular_color = vec4(0, 0, 0, 0);

	if (diffuse_factor > 0.0f)
	{
		vec3 fragment_to_eye = normalize(eye_position - fragment_position);
		vec3 reflected_vertex =  normalize(reflect(-direction, normalize(normal)));

		float specular_factor = dot(fragment_to_eye, reflected_vertex);
		if (specular_factor > 0.0f)
		{
			specular_factor = pow(specular_factor, material.shininess);
			specular_color = vec4(light.color * material.specular_intensity * specular_factor, 1.0f);
		}
	}

	return (ambient_color + (1.0 - shadow_factor) * (diffuse_color + specular_color));
}

//vec4 calculate_directional_light()
//{
//	// float shadow_factor = ca(DirectionalLightSpacePos);
//	return calculate_light_by_direction(directional_light.base, directional_light.direction);
//}

float calculate_point_shadow_factor(PointLight point_light, int shadow_index)
{
	vec3 frag_to_light = fragment_position - point_light.position;
	float current_depth = length(frag_to_light);

	float shadow = 0.0;
	float bias   = 0.15;
	int samples  = 20;

	float view_distance = length(eye_position - fragment_position);
	float disk_radius = (1.0 + (view_distance / omni_shadow_maps[shadow_index].far_plane)) / 25.0;
	for(int i = 0; i < samples; ++i)
	{
		float closest_depth = texture(omni_shadow_maps[shadow_index].shadow_map, frag_to_light + gridSamplingDisk[i] * disk_radius).r;
		closest_depth *= omni_shadow_maps[shadow_index].far_plane;   // Undo mapping [0;1]
		if(current_depth - bias > closest_depth)
			shadow += 1.0;
	}
	shadow /= float(samples);

	return shadow;
}

vec4 calculate_point_light(PointLight point_light, int shadow_index)
{
	vec3 direction = fragment_position - point_light.position;
	float distance = length(direction);
	direction = normalize(direction);

	float shadow_factor = calculate_point_shadow_factor(point_light, shadow_index);

	vec4 colour = calculate_light_by_direction(point_light.base, direction, shadow_factor);
	float attenuation = point_light.exponent * distance * distance +
	point_light.linear * distance +
	point_light.constant;

	return (colour / attenuation);
}

vec4 calculate_point_lights()
{
	vec4 total_color = vec4(0, 0, 0, 0);
	for(int i = 0; i < point_light_count; i++)
	{
		total_color += calculate_point_light(point_lights[i], i);
	}

	return total_color;
}

void main()
{
	// vec4 computed_color = calculate_directional_light();
	vec4 computed_color = calculate_point_lights();

	colour = vec4(vCol.r, vCol.g, vCol.b, 1.0f) * computed_color;
}