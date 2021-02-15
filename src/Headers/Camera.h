#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glfw/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat move_speed, GLfloat turn_speed);

	void key_controls(bool* keys, GLfloat delta_time);
	void mouse_controls(GLfloat x_change, GLfloat y_change, bool* mouse_buttons, GLfloat delta_time);

	void set_is_panning(bool is_panning) { this->is_panning = is_panning; }
	bool get_is_panning() { return is_panning;  }

	GLfloat get_zoom() { return zoom; };

	void zoom_in();
	void zoom_out();

	glm::mat4 calculate_view_matrix();

	~Camera();

private:
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

	bool is_panning = false;
	GLfloat zoom = 0.0f;

	void update();
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