#include "Camera.h"

Camera::Camera() {};

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat move_speed, GLfloat turn_speed)
{
	this->position = position;
	this->world_up = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->front = glm::vec3(0.0f, 0.0f, 0.0f);
	this->move_speed = move_speed;
	this->turn_speed = turn_speed;

	update();
}

void Camera::key_controls(bool* keys, GLfloat delta_time)
{
	GLfloat velocity = move_speed * delta_time;

	if (keys[GLFW_KEY_W])
	{
		position += front * move_speed;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * move_speed;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * move_speed;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * move_speed;
	}
}

void Camera::mouse_controls(GLfloat x_change, GLfloat y_change)
{
	x_change *= turn_speed;
	y_change *= turn_speed;

	yaw += x_change;
	pitch += y_change;

	// Limit our camera from circling behind when looking far up or down
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculate_view_matrix() const
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{

}