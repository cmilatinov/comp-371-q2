#include "Window.h"

Window::Window() {}

Window::Window(GLint width, GLint height)
{
	this->width = width;
	this->height = height;

	for (size_t i = 0; i < 1024; i++)
	{
		key_state[i] = 0;
	}
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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
}

void Window::link_callbacks()
{
	glfwSetKeyCallback(main_window, handle_keys);
	glfwSetCursorPosCallback(main_window, handle_mouse);
}

void Window::handle_keys(GLFWwindow* window, int key, int code, int action, int mode)
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
}

void Window::handle_mouse(GLFWwindow* window, double x_pos, double y_pos)
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

	// printf("X: %.6f Y: %.6f\n", theWindow->xChange, theWindow->yChange);
}

Window::~Window()
{
	glfwDestroyWindow(main_window);
	glfwTerminate();
}