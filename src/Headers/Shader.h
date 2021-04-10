#pragma once

#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <gl\glew.h>
#include <glm\gtc\type_ptr.hpp>

#define MAX_LIGHTS 5

using std::string;
using std::stringstream;

struct UniformLight {
    GLuint color;
    GLuint pos;
    GLuint dir;
    GLuint innerCutoff;
    GLuint outerCutoff;
    GLuint lightSpace;
    GLuint shadowMap;
};

class Shader
{
public:
	Shader(const char* vertex_file_path, const char* fragment_file_path);
    Shader(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path);
	void create_from_files(const char* vertex_file_path, const char* fragment_file_path);
    void create_from_files(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path);

	GLuint get_projection_location() const { return uniform_projection; };
	GLuint get_model_location() const { return uniform_model; };
	GLuint get_view_location() const { return uniform_view; };

    GLuint get_use_texture_location() const { return uniform_use_texture; };
    GLuint get_use_lighting_location() const { return uniform_use_lighting; };

	// Lighting
    GLuint get_eye_position_location() const { return uniform_eye_position; };
    GLuint get_specular_intensity_location() const { return uniform_specular_intensity; };
    GLuint get_shininess_location() const { return uniform_shininess; };

    // Shadow mapping
    GLuint get_num_lights_location() const { return uniform_num_lights; };
    GLuint get_light_space_location() const { return uniform_light_space; };
    const UniformLight * get_light_locations() const { return uniform_lights; };

    void toggle_shadows();

	void use_shader() const;
	void clear_shader();

	~Shader();

private:

    bool shadow_toggle = true;

	GLuint shader_ID = 0, uniform_projection = 0, uniform_model = 0, uniform_view = 0, uniform_eye_position = 0;
	GLuint uniform_use_texture = 0, uniform_use_lighting = 0;
	GLuint uniform_specular_intensity = 0, uniform_shininess = 0;

    UniformLight uniform_lights[MAX_LIGHTS];
    GLuint uniform_num_lights = 0;
    GLuint uniform_light_space = 0;

	std::string read_file(const char* file_path);
	void compile_shader(const char* vertex_code, const char* fragment_code);
    void compile_shader(const char* vertex_code, const char* fragment_code, const char* geometry_code);
	void compile_program();
	void add_shader(GLuint program, const char* shader_code, GLenum shader_type);
};

