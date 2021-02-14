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
	if (keys[GLFW_KEY_UP])
	{
		y_rotation += -2.5;
	}
	if (keys[GLFW_KEY_DOWN])
	{
		y_rotation += 2.5;
	}
	if (keys[GLFW_KEY_LEFT])
	{
		x_rotation += -2.5;
	}
	if (keys[GLFW_KEY_RIGHT])
	{
		x_rotation += 2.5;
	}
	if (keys[GLFW_KEY_HOME])
	{
		// Reset to default values
		x_rotation = 0;
		y_rotation = 0;
		front = glm::vec3(0.0f, 0.0f, 0.0f);
		position = glm::vec3(0.0f, 0.0f, 20.0f);
		world_up = glm::vec3(0.0f, 1.0f, 0.0f);
		yaw = -90.0;
		pitch = 0;
	}
}

void Camera::mouse_controls(GLfloat x_change, GLfloat y_change, bool* mouse_buttons)
{
	// Disable normal camera controls when the user is panning
	if (!mouse_buttons[GLFW_MOUSE_BUTTON_MIDDLE])
	{
		// Adjust the value changes by our speed modifiers
		x_change *= turn_speed;
		y_change *= turn_speed;
		// Apply changes to our yaw and pitch
		yaw += x_change;
		pitch += y_change;
		// Limit our camera from flipping when looking too far up or down
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
}

glm::mat4 Camera::calculate_view_matrix()
{
	glm::mat4 view_matrix = glm::lookAt(position, position + front, up);

	// If y rotation values are set apply the appropriate changes to our view matrix
	if (y_rotation != 0) {
		view_matrix = glm::rotate(view_matrix, glm::radians(y_rotation), glm::vec3(0.0f, -1.0f, 0.0f));
	}
	// If x rotation values are set apply the appropriate changes to our view matrix
	if (x_rotation != 0) {
		view_matrix = glm::rotate(view_matrix, glm::radians(x_rotation), glm::vec3(-1.0f, 0.0f, 0.0f));
	}

	return view_matrix;
}

void Camera::update()
{
	// Calculate the direction of our camera using the changes in our yaw and pitch
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