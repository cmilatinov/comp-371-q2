#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glfw/glfw3.h>

#include "Window.h"

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat move_speed, GLfloat turn_speed, Window* window);

	void key_controls(bool* keys, GLfloat delta_time);
	void mouse_controls(GLfloat x_change, GLfloat y_change, bool* mouse_buttons, GLfloat delta_time);

	GLfloat get_zoom() { return zoom; };

	void zoom_in();
	void zoom_out();
	

	glm::mat4 calculate_view_matrix();
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

	GLfloat zoom = 0.0f;

	glm::mat4 default_projection;

	glm::mat4 pan_translation;

	void update();

	const GLfloat DEFAULT_FOV = 45.0f;
};

inline void Camera::zoom_in() 
{
	if ((45 + zoom) >= 20) {
		this->zoom -= 1.0;
	}
}

inline void Camera::zoom_out() 
{
	if ((45 - zoom) >= 45) {
		this->zoom += 1.0;
	}
}