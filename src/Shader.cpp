#include "Shader.h"

Shader::Shader(const char* vertex_file_path, const char* fragment_file_path) {
    create_from_files(vertex_file_path, fragment_file_path);
}

Shader::Shader(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path) {
    create_from_files(vertex_file_path, fragment_file_path, geometry_file_path);
}

void Shader::create_from_files(const char* vertex_file_path, const char* fragment_file_path)
{
	std::string vertex_string = read_file(vertex_file_path);
	std::string fragment_string = read_file(fragment_file_path);

	const char* vertex_code = vertex_string.c_str();
	const char* fragment_code = fragment_string.c_str();

	compile_shader(vertex_code, fragment_code);
}

void Shader::create_from_files(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path)
{
    std::string vertex_string = read_file(vertex_file_path);
    std::string fragment_string = read_file(fragment_file_path);
    std::string geometry_string = read_file(geometry_file_path);

    const char* vertex_code = vertex_string.c_str();
    const char* fragment_code = fragment_string.c_str();
    const char* geometry_code = geometry_string.c_str();

    compile_shader(vertex_code, fragment_code, geometry_code);
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

void Shader::compile_shader(const char* vertex_code, const char* fragment_code)
{
	shader_ID = glCreateProgram();

	if (!shader_ID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	add_shader(shader_ID, vertex_code, GL_VERTEX_SHADER);
	add_shader(shader_ID, fragment_code, GL_FRAGMENT_SHADER);

    compile_program();
}

void Shader::compile_shader(const char* vertex_code, const char* fragment_code, const char* geometry_code)
{
    shader_ID = glCreateProgram();

    if (!shader_ID)
    {
        printf("Error creating shader program!\n");
        return;
    }

    add_shader(shader_ID, vertex_code, GL_VERTEX_SHADER);
    add_shader(shader_ID, fragment_code, GL_FRAGMENT_SHADER);
    add_shader(shader_ID, geometry_code, GL_GEOMETRY_SHADER);

    compile_program();
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

void Shader::set_point_light(PointLight p_light) const {
    p_light.use_light(
                uniform_point_light.uniform_ambient_intensity,
                uniform_point_light.uniform_color,
                uniform_point_light.uniform_diffuse_intensity,
                uniform_point_light.uniform_position,
                uniform_point_light.uniform_constant,
                uniform_point_light.uniform_linear,
                uniform_point_light.uniform_exponent);

        p_light.get_shadow_map()->read(GL_TEXTURE0);
        glUniform1i(uniform_omni_shadow_map.uniform_shadow_map, 0);
        glUniform1f(uniform_omni_shadow_map.uniform_far_plane, p_light.get_far_plane());
}

void Shader::set_light_matrices(std::vector<glm::mat4> light_matrices) {
    for(size_t i = 0; i < 6; i++)
    {
        glUniformMatrix4fv(uniform_light_matrices[i], 1, GL_FALSE, glm::value_ptr(light_matrices[i]));
    }
}

void Shader::compile_program() {
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

    // Lights + Phong
    uniform_eye_position = glGetUniformLocation(shader_ID, "eye_position");
    uniform_specular_intensity = glGetUniformLocation(shader_ID, "material.specular_intensity");
    uniform_shininess = glGetUniformLocation(shader_ID, "material.shininess");

    uniform_point_light.uniform_color = glGetUniformLocation(shader_ID, "point_light.base.color");
    uniform_point_light.uniform_ambient_intensity = glGetUniformLocation(shader_ID, "point_light.base.ambient_intensity");
    uniform_point_light.uniform_diffuse_intensity = glGetUniformLocation(shader_ID, "point_light.base.diffuse_intensity");
    uniform_point_light.uniform_position = glGetUniformLocation(shader_ID, "point_light.position");
    uniform_point_light.uniform_constant = glGetUniformLocation(shader_ID, "point_light.constant");
    uniform_point_light.uniform_linear = glGetUniformLocation(shader_ID, "point_light.linear");
    uniform_point_light.uniform_exponent = glGetUniformLocation(shader_ID, "point_light.exponent");

    // Shadow Map
    uniform_omni_light_pos = glGetUniformLocation(shader_ID, "light_pos");
    uniform_far_plane = glGetUniformLocation(shader_ID, "far_plane");

    for (size_t i = 0; i < 6; i++)
    {
        char location_buffer[100] = { '\0' };

        snprintf(location_buffer, sizeof(location_buffer), "light_matrices[%d]", i);
        uniform_light_matrices[i] = glGetUniformLocation(shader_ID, location_buffer);
    }

    uniform_omni_shadow_map.uniform_shadow_map = glGetUniformLocation(shader_ID, "omni_shadow_map.shadow_map");
    uniform_omni_shadow_map.uniform_far_plane = glGetUniformLocation(shader_ID, "omni_shadow_map.far_plane");
}

void Shader::toggle_shadows() {
    glUniform1i(glGetUniformLocation(shader_ID, "shadow_toggle"), !shadow_toggle);
    shadow_toggle = !shadow_toggle;
}
