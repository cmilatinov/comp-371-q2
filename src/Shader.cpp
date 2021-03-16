#include "Shader.h"

Shader::Shader(const char* vertex_file_path, const char* fragment_file_path) {
    create_from_files(vertex_file_path, fragment_file_path);
}

void Shader::create_from_files(const char* vertex_file_path, const char* fragment_file_path)
{
	std::string vertex_string = read_file(vertex_file_path);
	std::string fragment_string = read_file(fragment_file_path);

	const char* vertexCode = vertex_string.c_str();
	const char* fragmentCode = fragment_string.c_str();

	compile(vertexCode, fragmentCode);
}

std::string Shader::read_file(const char* file_path)
{
	std::string content;
	std::ifstream fileStream(file_path, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", file_path);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::compile(const char* vertex_code, const char* fragment_code)
{
	shader_ID = glCreateProgram();

	if (!shader_ID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	add_shader(shader_ID, vertex_code, GL_VERTEX_SHADER);
	add_shader(shader_ID, fragment_code, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar info_log[1024] = { 0 };

	glLinkProgram(shader_ID);
	glGetProgramiv(shader_ID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader_ID, sizeof(info_log), NULL, info_log);
		printf("Error linking program: '%s'\n", info_log);
		return;
	}

	glValidateProgram(shader_ID);
	glGetProgramiv(shader_ID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader_ID, sizeof(info_log), NULL, info_log);
		printf("Error validating program: '%s'\n", info_log);
		return;
	}

	uniform_projection = glGetUniformLocation(shader_ID, "projection");
	uniform_model = glGetUniformLocation(shader_ID, "model");
	uniform_view = glGetUniformLocation(shader_ID, "view");

    uniform_directional_light.uniform_color = glGetUniformLocation(shader_ID, "directional_light.base.color");
    uniform_directional_light.uniform_ambient_intensity = glGetUniformLocation(shader_ID, "directional_light.base.ambient_intensity");
    uniform_directional_light.uniform_direction = glGetUniformLocation(shader_ID, "directional_light.direction");
    uniform_directional_light.uniform_diffuse_intensity = glGetUniformLocation(shader_ID, "directional_light.base.diffuse_intensity");

    uniform_eye_position = glGetUniformLocation(shader_ID, "eye_position");
    uniform_specular_intensity = glGetUniformLocation(shader_ID, "material.specular_intensity");
    uniform_shininess = glGetUniformLocation(shader_ID, "material.shininess");

    uniform_point_light_count = glGetUniformLocation(shader_ID, "point_light_count");

    for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        char location_buffer[100] = { '\0' };

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].base.color", i);
        uniform_point_light[i].uniform_color = glGetUniformLocation(shader_ID, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].base.ambient_intensity", i);
        uniform_point_light[i].uniform_ambient_intensity = glGetUniformLocation(shader_ID, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].base.diffuse_intensity", i);
        uniform_point_light[i].uniform_diffuse_intensity = glGetUniformLocation(shader_ID, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].position", i);
        uniform_point_light[i].uniform_position = glGetUniformLocation(shader_ID, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].constant", i);
        uniform_point_light[i].uniform_constant = glGetUniformLocation(shader_ID, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].linear", i);
        uniform_point_light[i].uniform_linear = glGetUniformLocation(shader_ID, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].exponent", i);
        uniform_point_light[i].uniform_exponent = glGetUniformLocation(shader_ID, location_buffer);
    }
}

void Shader::use_shader() const
{
	glUseProgram(shader_ID);
}

void Shader::clear_shader()
{
	if (shader_ID != 0)
	{
		glDeleteProgram(shader_ID);
		shader_ID = 0;
	}

	uniform_model = 0;
	uniform_projection = 0;
	uniform_view = 0;
}


void Shader::add_shader(GLuint program, const char* shader_code, GLenum shader_type)
{
	GLuint new_shader = glCreateShader(shader_type);

	glShaderSource(new_shader, 1, &shader_code, NULL);
	glCompileShader(new_shader);

	GLint result = 0;
	GLchar info_log[1024] = { 0 };

	glGetShaderiv(new_shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(new_shader, sizeof(info_log), NULL, info_log);
		printf("Error compiling the %d shader: '%s'\n", shader_type, info_log);
		return;
	}

	glAttachShader(program, new_shader);
}

Shader::~Shader()
{
	clear_shader();
}

void Shader::set_directional_light(DirectionalLight *d_light) {
    d_light->use_light(uniform_directional_light.uniform_ambient_intensity,
                       uniform_directional_light.uniform_color,
                       uniform_directional_light.uniform_diffuse_intensity,
                       uniform_directional_light.uniform_direction);
}

void Shader::set_point_lights(PointLight *p_lights, unsigned int count) {
    if (count > MAX_POINT_LIGHTS)
        point_light_count = MAX_POINT_LIGHTS;
    else
        point_light_count = count;

    glUniform1i(uniform_point_light_count, point_light_count);

    for (size_t i = 0; i < point_light_count; i++)
    {
        p_lights[i].use_light(
                uniform_point_light[i].uniform_ambient_intensity,
                uniform_point_light[i].uniform_color,
                uniform_point_light[i].uniform_diffuse_intensity,
                uniform_point_light[i].uniform_position,
                uniform_point_light[i].uniform_constant,
                uniform_point_light[i].uniform_linear,
                uniform_point_light[i].uniform_exponent);
    }
}
