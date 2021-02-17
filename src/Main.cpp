#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Line.h"
#include "Grid.h"
#include "MeshLoader.h"
#include "EntityRenderer.h"
#include "EntityManager.h"
#include "Cube.h"

#define PI 3.14159265358979f

const float to_radians = PI / 180.0f;

// When debugging, the code will execute from "out/build/x64-Debug/". That last folder will have the name of your configuration.
// We need to go three levels back to the root directory and into "src" before we can see the "Shaders" folder.
// The build directory might be different with other IDEs and OS, just add a preprocessor conditional statement for your case when you encounter it.
// Vertex Shader file path
static const char * vertex_path = "Shaders/shader.vert";
// Fragment Shader file path
static const char * fragment_path = "Shaders/shader.frag";

void create_entities(MeshLoader & loader, EntityManager & entityManager) {
    const Mesh * cube = loader.create_mesh(CUBE_VERTEX_ARRAY, sizeof(CUBE_VERTEX_ARRAY) / sizeof(glm::vec3));

    // LETTER S

    Entity * s_1 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 2.5f, 0));

    Entity * s_2 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 5.5f, 0));

    Entity * s_3 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 8.5f, 0));

    Entity * s_4 = (new Entity(cube))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(1.25f, 4, 0));

    Entity * s_5 = (new Entity(cube))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(-1.25f, 7, 0));

    EntityGroup * letter_s = (new EntityGroup())
            ->add(s_1)
            ->add(s_2)
            ->add(s_3)
            ->add(s_4)
            ->add(s_5);

    // LETTER C

    Entity * c_1 = (new Entity(cube))
            ->scale(vec3(0.7f, 5, 1))
            ->translate(vec3(0, 5.5f, 0));

    Entity * c_2 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 2.5f, 0));

    Entity * c_3 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 8.5f, 0));

    EntityGroup * letter_c = (new EntityGroup())
            ->translate(vec3(5, 0, 0))
            ->add(c_1)
            ->add(c_2)
            ->add(c_3);

    // LETTER N

    Entity * n_1 = (new Entity(cube))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(0, -0.5f, 0));

    Entity * n_2 = (new Entity(cube))
            ->scale(vec3(3, 1, 1))
            ->translate(vec3(1.5f, 3, 0));

    Entity * n_3 = (new Entity(cube))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(3, -0.5f, 0));

    EntityGroup * letter_n = (new EntityGroup())
            ->translate(vec3(10, 5.5f, 0))
            ->add(n_1)
            ->add(n_2)
            ->add(n_3);

    // LETTER M

    Entity * m_1 = (new Entity(cube))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(0, -0.5f, 0));

    Entity * m_2 = (new Entity(cube))
            ->scale(vec3(6, 1, 1))
            ->translate(vec3(3, 3, 0));

    Entity * m_3 = (new Entity(cube))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(3, -0.5f, 0));

    Entity * m_5 = (new Entity(cube))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(6, -0.5f, 0));

    EntityGroup * letter_m = (new EntityGroup())
            ->translate(vec3(16, 5.5f, 0))
            ->add(m_1)
            ->add(m_2)
            ->add(m_3)
            ->add(m_5);

    // LETTER I

    Entity * i_1 = (new Entity(cube))
        ->scale(vec3(0.7f, 7, 1))
        ->translate(vec3(0, 5.5f, 0));

    EntityGroup * letter_i = (new EntityGroup())
            ->translate(vec3(25, 0, 0))
            ->add(i_1);


    // Number 2 4 6 7 8

    // NUMBER 2
    Entity * nb2_1 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 2.5f, 0));

    Entity * nb2_2 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 5.5f, 0));

    Entity * nb2_3 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 8.5f, 0));

    Entity * nb2_4 = (new Entity(cube))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(1.25f, 7, 0));

    Entity * nb2_5 = (new Entity(cube))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(-1.25f, 4, 0));

    EntityGroup * number_2 = (new EntityGroup())
            ->translate(vec3(30, 0, 0))
            ->add(nb2_1)
            ->add(nb2_2)
            ->add(nb2_3)
            ->add(nb2_4)
            ->add(nb2_5);

    // NUMBER 4
    Entity * nb4_1 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 5.5f, 0));


    Entity * nb4_3 = (new Entity(cube))
            ->scale(vec3(0.6f, 7, 1))
            ->translate(vec3(1.25f, 5.5f, 0));

    Entity * nb4_4 = (new Entity(cube))
            ->scale(vec3(0.6f, 3.5f, 1))
            ->translate(vec3(-1.25f, 7.25f, 0));

    EntityGroup * number_4 = (new EntityGroup())
            ->translate(vec3(35, 0, 0))
            ->add(nb4_1)
            ->add(nb4_3)
            ->add(nb4_4);

    // NUMBER 6
    Entity * nb6_1 = (new Entity(cube))
            ->scale(vec3(0.7f, 5, 1))
            ->translate(vec3(0, 5.5f, 0));

    Entity * nb6_2 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 2.5f, 0));

    Entity * nb6_3 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 5.5f, 0));

    Entity * nb6_4 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 8.5f, 0));

    Entity * nb6_5 = (new Entity(cube))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(2.5f, 4, 0));

    EntityGroup * number_6 = (new EntityGroup())
            ->translate(vec3(40, 0, 0))
            ->add(nb6_1)
            ->add(nb6_2)
            ->add(nb6_3)
            ->add(nb6_4)
            ->add(nb6_5);

    // NUMBER 7
    Entity * nb7_1 = (new Entity(cube))
            ->scale(vec3(0.6f, 6.5f, 1))
            ->translate(vec3(1.5f, 5, 0))
            ->rotate(vec3(0, 0, -20));

    Entity * nb7_2 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 8.5f, 0));

    EntityGroup * number_7 = (new EntityGroup())
            ->translate(vec3(45, 0, 0))
            ->add(nb7_1)
            ->add(nb7_2);

    // NUMBER 8
    Entity * nb8_1 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 2.5f, 0));

    Entity * nb8_2 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 5.5f, 0));

    Entity * nb8_3 = (new Entity(cube))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 8.5f, 0));

    Entity * nb8_4 = (new Entity(cube))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(2.5f, 4, 0));

    Entity * nb8_5 = (new Entity(cube))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(2.5f, 7, 0));

    Entity * nb8_6 = (new Entity(cube))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(0, 4, 0));

    Entity * nb8_7 = (new Entity(cube))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(0, 7, 0));

    EntityGroup * number_8 = (new EntityGroup())
            ->translate(vec3(50, 0, 0))
            ->add(nb8_1)
            ->add(nb8_2)
            ->add(nb8_3)
            ->add(nb8_4)
            ->add(nb8_5)
            ->add(nb8_6)
            ->add(nb8_7);

    // Add letter instances
    entityManager.add(letter_s);
    entityManager.add(letter_c);
    entityManager.add(letter_n);
    entityManager.add(letter_m);
    entityManager.add(letter_i);
    entityManager.add(number_2);
    entityManager.add(number_4);
    entityManager.add(number_6);
    entityManager.add(number_7);
    entityManager.add(number_8);



    // TODO add all letters
}


int main() {
    // Window creation
    Window main_window(1920, 1080);
	int result = main_window.init();
	if (result == 1) {
		// Error creating the GLFW window so terminate early
		return 1;
	}

    // Load shader program
	Shader app_shader(vertex_path, fragment_path);
    // Load perspective matrix only ONCE, will not change later for now
    // This part should actually be in the camera
    // it should create a single pre-multiplied projection-view matrix
    // because it allows us to change the camera's FOV if needed later
    mat4 projection = glm::perspective(45.0f * to_radians, main_window.get_buffer_width() / main_window.get_buffer_width(), 0.1f, 1000.0f);
    app_shader.use_shader();
	glUniformMatrix4fv(app_shader.get_projection_location(), 1, GL_FALSE, glm::value_ptr(projection));

	// Init entity renderer and manager, create necessary entities
	EntityRenderer entityRenderer(app_shader);
	EntityManager entityManager;
    MeshLoader loader;
    create_entities(loader, entityManager);

    // Creates the camera, used as an abstraction to calculate the view matrix
    Camera camera(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.4f, 0.2f);

	// Creates the X, Y, Z axis lines
	Line line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Line line2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 7.0f),glm::vec3(0.0f, 0.0f, 1.0f));
	Line line3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Creates the grid
	Grid grid(glm::vec3(0.f, 0.f, 0.f));

    // Enable depth in our view space
    glEnable(GL_DEPTH_TEST);

    // Set clear color to white
    glClearColor(1, 1, 1, 1);

	// Loop until window closed
    GLfloat last_time = 0;
	while (!main_window.should_close())
	{
		GLfloat now = glfwGetTime();
        GLfloat delta_time = now - last_time;
		last_time = now;

		// Get user input events
		glfwPollEvents();

		camera.key_controls(main_window.get_keys(), delta_time);
		camera.mouse_controls(main_window.get_x_change(), main_window.get_y_change());

		// Clear window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render entities
        entityRenderer.render(camera, entityManager);

		// Display the axis lines
		line.render();
		line2.render();
		line3.render();

		// Display the grid
		grid.render();

		// Stop the shader
		glUseProgram(0);

		// Display the newly rendered buffer in the window
		main_window.swap_buffers();

	}

	return 0;
}