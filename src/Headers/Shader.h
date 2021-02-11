#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	Shader();
	void create_from_files(const char* vertex_file_path, const char* fragment_file_path);

	GLuint get_projection_location() { return uniform_projection; };
	GLuint get_model_location() { return uniform_model; };
	GLuint get_view_location() { return uniform_view; };

	void use_shader();
	void clear_shader();

	~Shader();

private:
	GLuint shader_ID, uniform_projection, uniform_model, uniform_view;
	
	std::string read_file(const char* file_path);
	void compile(const char* vertex_code, const char* fragment_code);
	void add_shader(GLuint program, const char* shader_code, GLenum shader_type);
};

