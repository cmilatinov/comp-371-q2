#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* Container class for functionality related to the GLFW Window instance */
class Window
{
public:
	Window();
	Window(GLint width, GLint height);
	~Window();
	// Initialize the GLFW window
	int init();
	// Get change in x mouse coordinates since last update
	GLfloat get_x_change();
	// Get change in y mouse coordinates since last update
	GLfloat get_y_change();
	GLfloat get_buffer_width() { return buffer_width; }
	bool* get_keys() { return key_state; }
	GLfloat get_buffer_height() { return buffer_height; }
	// Check whether the GLFW window should be closed
	bool should_close() { return glfwWindowShouldClose(main_window); }
	void swap_buffers() { glfwSwapBuffers(main_window); }
private:
	// Store the instance of our GLFW window
	GLFWwindow* main_window;
	// Dimensions of the window
	GLint width, height;
	// Dimensions of the observable OpenGL view (excluding border/titlebar)
	GLint buffer_width, buffer_height;
	// Boolean array containing up to date key press state
	bool key_state[1024];
	//
	GLfloat last_x, last_y;
	//
	GLfloat x_change = 0.0f, y_change = 0.0f;
	// Prevent the camera from jerking when the mouse moves in from outside the frame
	bool initial_mouse_move;
	// Set the callback handlers to be used by GLFW
	void link_callbacks();

	// Callback function to be called by GLFW on key press state changes
	static void handle_keys(GLFWwindow* window, int key, int code, int action, int mode);
	// Callback function to be called by GLFW on mouse movement state changes
	static void handle_mouse(GLFWwindow* window, double x_pos, double y_pos);
};

inline GLfloat Window::get_x_change()
{
	GLfloat difference = x_change;
	x_change = 0.0f;
	return difference;
}

inline GLfloat Window::get_y_change()
{
	GLfloat difference = y_change;
	y_change = 0.0f;
	return difference;
}