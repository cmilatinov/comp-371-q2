#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <gl\glew.h>

#include "DirectionalLight.h"
#include "PointLight.h"

class Shader
{
public:
	Shader(const char* vertex_file_path, const char* fragment_file_path);
	void create_from_files(const char* vertex_file_path, const char* fragment_file_path);

	GLuint get_projection_location() const { return uniform_projection; };
	GLuint get_model_location() const { return uniform_model; };
	GLuint get_view_location() const { return uniform_view; };
    GLuint get_eye_position_location() { return uniform_eye_position; };
    GLuint get_specular_intensity_location() { return uniform_specular_intensity; };
    GLuint get_shininess_location() { return uniform_shininess; };

    void set_directional_light(DirectionalLight * d_light);
    void set_point_lights(PointLight * p_lights, unsigned int count);

	void use_shader() const;
	void clear_shader();

	~Shader();

private:
    int point_light_count = 0;
    static const int MAX_POINT_LIGHTS = 3;

    GLuint uniform_point_light_count;

    struct {
        GLuint uniform_color;
        GLuint uniform_ambient_intensity;
        GLuint uniform_diffuse_intensity;
        GLuint uniform_direction;
    } uniform_directional_light;

    struct {
        GLuint uniform_color;
        GLuint uniform_ambient_intensity;
        GLuint uniform_diffuse_intensity;
        GLuint uniform_position;
        GLuint uniform_constant;
        GLuint uniform_linear;
        GLuint uniform_exponent;
    } uniform_point_light[MAX_POINT_LIGHTS];


	GLuint shader_ID = 0, uniform_projection = 0, uniform_model = 0, uniform_view = 0, uniform_eye_position = 0;
	GLuint uniform_specular_intensity = 0, uniform_shininess = 0;

	std::string read_file(const char* file_path);
	void compile(const char* vertex_code, const char* fragment_code);
	void add_shader(GLuint program, const char* shader_code, GLenum shader_type);
};

