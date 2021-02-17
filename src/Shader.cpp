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
