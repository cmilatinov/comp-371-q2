#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <gl\glew.h>

class Shader
{
public:
	Shader(const char* vertex_file_path, const char* fragment_file_path);
	void create_from_files(const char* vertex_file_path, const char* fragment_file_path);

	GLuint get_projection_location() const { return uniform_projection; };
	GLuint get_model_location() const { return uniform_model; };
	GLuint get_view_location() const { return uniform_view; };

	void use_shader() const;
	void clear_shader();

	~Shader();

private:
	GLuint shader_ID = 0, uniform_projection = 0, uniform_model = 0, uniform_view = 0;
	
	std::string read_file(const char* file_path);
	void compile(const char* vertex_code, const char* fragment_code);
	void add_shader(GLuint program, const char* shader_code, GLenum shader_type);
};

