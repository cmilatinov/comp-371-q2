#include "Window.h"

Window::Window() {
    for (size_t i = 0; i < 1024; i++) {
        if (i < 8) {
            mouse_button_state[i] = 0;
        }
    }
}

Window::Window(GLint width, GLint height) {
	this->width = width;
	this->height = height;
}

int Window::init()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		printf("GLFW init failed");

		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile = No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	// Allow forward compatability
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create our GLFW window instance
	main_window = glfwCreateWindow(width, height, ":^)", NULL, NULL);

	if (!main_window)
	{
		printf("GLFW window creation failed");
		glfwTerminate();

		return 1;
	}

	// Get buffer size ifnromation
	glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height);

	// Set context for GLEW to use
	glfwMakeContextCurrent(main_window);

	// Set GLFW state callbacks
	link_callbacks();

	// Locks the cursor to the window instance
	glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("GLEW initialization failed: %s", glewGetErrorString(error));
		glfwDestroyWindow(main_window);
		glfwTerminate();

		return 1;
	}

	// glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, buffer_width, buffer_height);

	glfwSetWindowUserPointer(main_window, this);

	return 0;
}

void Window::link_callbacks()
{
	glfwSetKeyCallback(main_window, handle_keys);
	glfwSetCursorPosCallback(main_window, handle_mouse_movement);
	glfwSetMouseButtonCallback(main_window, handle_mouse_buttons);
}

void Window::handle_keys(GLFWwindow* window, int key, int code, int action, int mods)
{
	// Our Window class callback function is static so we cast to get an instance of our class
	Window* window_instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			window_instance->key_state[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			window_instance->key_state[key] = false;
		}
	}

	// Chose the polygon mode for rendering
	if (window_instance->key_state[GLFW_KEY_O])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (window_instance->key_state[GLFW_KEY_P])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	else if (window_instance->key_state[GLFW_KEY_T])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

    window_instance->key_callback(key, code, action, mods);
}

void Window::handle_mouse_movement(GLFWwindow* window, double x_pos, double y_pos)
{
	// Our Window class callback function is static so we cast to get an instance of our class
	Window* window_instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (window_instance->initial_mouse_move)
	{
		window_instance->last_x = x_pos;
		window_instance->last_y = y_pos;
		window_instance->initial_mouse_move = false;
	}

	window_instance->x_change = x_pos - window_instance->last_x;
	window_instance->y_change = window_instance->last_y - y_pos;

	window_instance->last_x = x_pos;
	window_instance->last_y = y_pos;

	// printf("X: %.6f Y: %.6f\n", window_instance->get_x_change(), window_instance->get_y_change());
}

void Window::handle_mouse_buttons(GLFWwindow* window, int button, int action, int mods)
{
	// Our Window class callback function is static so we cast to get an instance of our class
	Window* window_instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (button >= 0 && button < 8)
	{
		if (action == GLFW_PRESS)
		{
			window_instance->mouse_button_state[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			window_instance->mouse_button_state[button] = false;
		}
	}
}

Window::~Window()
{
	glfwDestroyWindow(main_window);
	glfwTerminate();
}