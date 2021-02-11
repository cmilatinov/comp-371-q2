#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Line.h"

const float to_radians = 3.14159265358979f / 180.0f;

Window main_window;

std::vector<Mesh*> mesh_list;
Shader app_shader;
Camera camera;

GLfloat delta_time = 0.0f;
GLfloat last_time = 0.0f;

// When debugging, the code will execute from "out/build/x64-Debug/". That last folder will have the name of your configuration.
// We need to go three levels back to the root directory and into "src" before we can see the "Shaders" folder.
// The build directory might be different with other IDEs and OS, just add a preprocessor conditional statement for your case when you encounter it.
// Vertex Shader file path
static const char* vertex_path = "../../../src/Shaders/shader.vert";
// Fragment Shader file path
static const char* fragment_path = "../../../src/Shaders/shader.frag";

void create_objects()
{
	// Example using cube from Lab03
	glm::vec3 vertexArray[] = {
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f), //left - red
		glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),

		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f),

		glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f), // far - blue
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f),

		glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f, 1.0f),

		glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f), // bottom - turquoise
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 1.0f),

		glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 1.0f),

		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), // near - green
		glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),

		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),

		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f), // right - purple
		glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 1.0f),

		glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f),

		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), // top - yellow
		glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 0.0f),

		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)
	}; // 72

	Mesh* obj1 = new Mesh();
	obj1->create_mesh(vertexArray, sizeof(vertexArray)/sizeof(glm::vec3), (sizeof(vertexArray) / sizeof(glm::vec3))/2);
	mesh_list.push_back(obj1);
}


void create_shader()
{
	app_shader = Shader();
	app_shader.create_from_files(vertex_path, fragment_path);
}

int main()
{
	main_window = Window(1024, 1024);
	int result = main_window.init();

	if (result == 1)
	{
		// Error creating the GLFW window so terminate early
		return 1;
	}

	create_objects();
	create_shader();

	camera = Camera(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.4f, 0.2f);

	GLuint uniform_projection = 0, uniform_model = 0, uniform_view = 0;

	glm::mat4 projection = glm::perspective(45.0f * to_radians, main_window.get_buffer_width() / main_window.get_buffer_width(), 0.1f, 100.0f);

	// Creates the X, Y, Z axis lines
	Line line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Line line2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 7.0f),glm::vec3(0.0f, 0.0f, 1.0f));
	Line line3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Loop until window closed
	while (!main_window.should_close())
	{
		GLfloat now = glfwGetTime();
		delta_time = now - last_time;
		last_time = now;

		// Get user input events
		glfwPollEvents();

		// Enable depth in our view space
		glEnable(GL_DEPTH_TEST);

		camera.key_controls(main_window.get_keys(), delta_time);
		camera.mouse_controls(main_window.get_x_change(), main_window.get_y_change());

		// Clear window
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use shader and retrieve our uniform values
		app_shader.use_shader();
		uniform_model = app_shader.get_model_location();
		uniform_projection = app_shader.get_projection_location();
		uniform_view = app_shader.get_view_location();

		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// Create identity matrix for transformations
		glm::mat4 model(1.0f);


		// TODO: Move this crap into it's own function and implement proper hierarchical modelling for rotations and transforms
		// DISPLAY S
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(5.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
		mesh_list[0]->render_mesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
		mesh_list[0]->render_mesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 6.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
		mesh_list[0]->render_mesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
		mesh_list[0]->render_mesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, 4.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
		mesh_list[0]->render_mesh();
		// END DISPLAY S



		model = glm::mat4(1.0f);
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

		// Display the axis lines
		line.render();
		line2.render();
		line3.render();

		glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));

		glUseProgram(0);

		main_window.swap_buffers();
	}

	return 0;
}