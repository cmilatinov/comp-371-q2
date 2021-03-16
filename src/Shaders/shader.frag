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

uniform int point_light_count;

uniform DirectionalLight directional_light;
uniform PointLight point_lights[MAX_POINT_LIGHTS];

uniform Material material;
// Camera position
uniform vec3 eye_position;

vec4 calculate_light_by_direction(Light light, vec3 direction)
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

	return (ambient_color + diffuse_color + specular_color);
}

vec4 calculate_directional_light()
{
	return calculate_light_by_direction(directional_light.base, directional_light.direction);
}

vec4 calculate_point_lights()
{
	vec4 total_color = vec4(0, 0, 0, 0);

	for (int i = 0; i < point_light_count; i++)
	{
		// Get the direction based on the position of the light from the fragment
		vec3 direction = fragment_position - point_lights[i].position;
		// Store the length before we normalize it
		float distance = length(direction);
		direction = normalize(direction);

		vec4 color = calculate_light_by_direction(point_lights[i].base, direction);
		// Quadratic formula
		float attenuation = (point_lights[i].exponent * (distance * distance) +
					point_lights[i].linear * distance +
					point_lights[i].constant);

		total_color += (color / attenuation);
	}

	return total_color;
}

void main()
{
	vec4 computed_color = calculate_directional_light();
	computed_color += calculate_point_lights();

	colour = vec4(vCol.r, vCol.g, vCol.b, 1.0f) * computed_color;
}