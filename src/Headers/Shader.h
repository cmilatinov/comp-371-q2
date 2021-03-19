#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <gl\glew.h>
#include <glm\gtc\type_ptr.hpp>

#include "DirectionalLight.h"
#include "PointLight.h"

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
	// Lighting
    GLuint get_eye_position_location() { return uniform_eye_position; };
    GLuint get_specular_intensity_location() { return uniform_specular_intensity; };
    GLuint get_shininess_location() { return uniform_shininess; };
    // Shadow maps
    GLuint get_omni_light_pos_location() { return uniform_omni_light_pos; };
    GLuint get_far_plane_location() { return uniform_far_plane; };

    void set_directional_light(DirectionalLight * d_light);
    void set_point_light(PointLight p_lights) const;
    void set_light_matrices(std::vector<glm::mat4> light_matrices);

    void toggle_shadows();

	void use_shader() const;
	void clear_shader();

	~Shader();

private:
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
    } uniform_point_light;

    struct {
        GLuint uniform_shadow_map;
        GLuint uniform_far_plane;
    } uniform_omni_shadow_map;

    bool shadow_toggle = true;

	GLuint shader_ID = 0, uniform_projection = 0, uniform_model = 0, uniform_view = 0, uniform_eye_position = 0;
	GLuint uniform_specular_intensity = 0, uniform_shininess = 0;
	GLuint uniform_omni_light_pos = 0, uniform_far_plane = 0;
	GLuint uniform_light_matrices[6];

	std::string read_file(const char* file_path);
	void compile_shader(const char* vertex_code, const char* fragment_code);
    void compile_shader(const char* vertex_code, const char* fragment_code, const char* geometry_code);
	void compile_program();
	void add_shader(GLuint program, const char* shader_code, GLenum shader_type);
};

