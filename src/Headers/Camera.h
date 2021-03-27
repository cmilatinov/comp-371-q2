#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include "Window.h"
#include "EntityGroup.h"

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat move_speed, GLfloat turn_speed, Window* window);

	void key_controls(bool* keys, GLfloat delta_time, EntityGroup* const selectedModel);
	void mouse_controls(GLfloat x_change, GLfloat y_change, bool* mouse_buttons, GLfloat delta_time);

	glm::vec3 get_camera_position() { return position; }

	glm::mat4 calculate_view_matrix() const;
	glm::mat4 calculate_projection();

private:
	Window* window;

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat y_rotation = 0;
	GLfloat x_rotation = 0;

	GLfloat move_speed;
	GLfloat turn_speed;

	GLfloat fov;

	glm::mat4 default_projection;

	void update();

	const GLfloat DEFAULT_FOV = 45.0f, MIN_FOV = 10.0F, MAX_FOV = 65.0F;
};