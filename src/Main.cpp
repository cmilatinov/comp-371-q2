#include <cmath>
#include <cstdlib>
#include <ctime>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Line.h"
#include "Grid.h"
#include "AssetLoader.h"
#include "SceneRenderer.h"
#include "SpotlightManager.h"
#include "EntityManager.h"

// When debugging, the code will execute from "out/build/x64-Debug/". That last folder will have the name of your configuration.
// We need to go three levels back to the root directory and into "src" before we can see the "Shaders" folder.
// The build directory might be different with other IDEs and OS, just add a preprocessor conditional statement for your case when you encounter it.
// Vertex Shader file path
static const char * vertex_path = "Shaders/shader.vert";
// Fragment Shader file path
static const char * fragment_path = "Shaders/shader.frag";

// Shadow Map Shader vertex file path
static const char * shadow_vertex_path = "Shaders/shadow.vert";
// Shadow Map Shader fragment file path
static const char * shadow_fragment_path = "Shaders/shadow.frag";

// Skybox Shader vertex file path
static const char * skybox_vertex_path = "Shaders/skybox.vert";
// Skybox Shader fragment file path
static const char * skybox_fragment_path = "Shaders/skybox.frag";

void create_entities(AssetLoader & loader, EntityManager & entityManager, EntityGroup ** groups) {

    const Texture * metalFinish = loader.load_texture_2d("Metal-Finish.jpg");
    const Texture * green = loader.load_texture_2d("green.png");
    const Texture * blue = loader.load_texture_2d("blue.png");

    const Mesh * axis = loader.load_mesh("axis.obj");

    // AXES
    TexturedMesh * axisXMesh = new TexturedMesh(axis, metalFinish);
    TexturedMesh * axisYMesh = new TexturedMesh(axis, green);
    TexturedMesh * axisZMesh = new TexturedMesh(axis, blue);

    Entity * axisX = (new Entity(axisXMesh))
            ->rotate(vec3(0, 0, -90));
    Entity * axisY = (new Entity(axisYMesh));
    Entity * axisZ = (new Entity(axisZMesh))
            ->rotate(vec3(90, 0, 0));

    entityManager.add(axisX);
    entityManager.add(axisY);
    entityManager.add(axisZ);

    // LETTERS
    const Mesh * cube = loader.load_mesh("cube.obj");
    const Mesh * sphere = loader.load_mesh("sphere.obj");

    TexturedMesh * cubeMesh = new TexturedMesh(cube, metalFinish);
    TexturedMesh * sphereMesh = new TexturedMesh(sphere, metalFinish);

    Entity * m_1 = (new Entity(cubeMesh))
            ->translate(vec3(0.2f, 1.3f, 0))
            ->rotate(vec3(0, 0, 45))
            ->scale(vec3(1, 0.5f, 0.25f));
    Entity * m_2 = (new Entity(cubeMesh))
            ->translate(vec3(-0.2f, 1.3f, 0))
            ->rotate(vec3(0, 0, -45))
            ->scale(vec3(1, 0.5f, 0.25f));
    Entity * m_3 = (new Entity(sphereMesh))
            ->translate(vec3(0.6f, 1, 0))
            ->scale(vec3(0.25f, 1, 0.25f));
    Entity * m_4 = (new Entity(sphereMesh))
            ->translate(vec3(-0.6f, 1, 0))
            ->scale(vec3(0.25f, 1, 0.25f));

    EntityGroup * letter_m = (new EntityGroup())
            ->translate(vec3(0, 12.5f, 0))
            ->add(m_1)
            ->add(m_2)
            ->add(m_3)
            ->add(m_4);


    Entity * i_1 = (new Entity(sphereMesh))
            ->translate(vec3(0, 1, 0))
            ->scale(vec3(0.25f, 1, 0.25f));

    EntityGroup * letter_i = (new EntityGroup())
            ->translate(vec3(0, 0, 0))
            ->add(i_1);

    EntityGroup * letter_i2 = (new EntityGroup())
            ->translate(vec3(0, 10, 0))
            ->add(i_1);


    Entity * l_1 = (new Entity(sphereMesh))
            ->translate(vec3(-0.5f, 1, 0))
            ->scale(vec3(0.25f, 1, 0.25f));
    Entity * l_2 = (new Entity(cubeMesh))
            ->translate(vec3(0, 0.25f, 0))
            ->scale(vec3(1, 0.5f, 0.25f));

    EntityGroup * letter_l = (new EntityGroup())
            ->translate(vec3(0, 7.5f, 0))
            ->add(l_1)
            ->add(l_2);


    Entity * a_1 = (new Entity(cubeMesh))
            ->rotate(vec3(90, 0, 0))
            ->translate(vec3(0, 0.70f, 0))
            ->scale(vec3(1, 0.5f, 0.25f));
    Entity * a_2 = (new Entity(cubeMesh))
            ->translate(vec3(-0.5f, 0.5f, 0))
            ->rotate(vec3(0, 0, 70))
            ->scale(vec3(1, 0.5f, 0.25f));
    Entity * a_3 = (new Entity(cubeMesh))
            ->translate(vec3(-0.17f, 1.4f, 0))
            ->rotate(vec3(0, 0, 70))
            ->scale(vec3(1, 0.5f, 0.25f));
    Entity * a_4 = (new Entity(cubeMesh))
            ->translate(vec3(0.5f, 0.5f, 0))
            ->rotate(vec3(0, 0, -70))
            ->scale(vec3(1, 0.5f, 0.25f));
    Entity * a_5 = (new Entity(cubeMesh))
            ->translate(vec3(0.17f, 1.4f, 0))
            ->rotate(vec3(0, 0, -70))
            ->scale(vec3(1, 0.5f, 0.25f));

    EntityGroup * letter_a = (new EntityGroup())
            ->translate(vec3(0, 5, 0))
            ->add(a_1)
            ->add(a_2)
            ->add(a_3)
            ->add(a_4)
            ->add(a_5);


    Entity * t_1 = (new Entity(sphereMesh))
            ->translate(vec3(0, 1, 0))
            ->scale(vec3(0.25f, 1, 0.25f));
    Entity * t_2 = (new Entity(cubeMesh))
            ->translate(vec3(0, 2, 0))
            ->scale(vec3(1, 0.5f, 0.25f));

    EntityGroup * letter_t = (new EntityGroup())
            ->translate(vec3(0, 2.5f, 0))
            ->add(t_1)
            ->add(t_2);

    EntityGroup * letters = (new EntityGroup())
            ->add(letter_m)
            ->add(letter_i2)
            ->add(letter_l)
            ->add(letter_a)
            ->add(letter_t)
            ->add(letter_i)
            ->scale(vec3(2.0f))
            ->translate(vec3(0, 0, -10));

    entityManager.add(letters);

    // Spotlight
    const Mesh * spotlightMesh = loader.load_mesh("spotlight.obj");
    TexturedMesh * spotlightTexturedMesh = new TexturedMesh(spotlightMesh, metalFinish);

    Entity * spotlight = (new Entity(spotlightTexturedMesh))
            ->translate(vec3(0, 73, 30))
            ->rotate(vec3(51.3401917, 0, 0));

    entityManager.add(spotlight);

    groups[0] = letter_m;
    groups[1] = letter_i2;
    groups[2] = letter_l;
    groups[3] = letter_a;
    groups[4] = letter_t;
    groups[5] = letter_i;

}

int main() {
    // Window creation
    Window main_window(1024, 768);
	int result = main_window.init();
	if (result == 1) {
		// Error creating the GLFW window so terminate early
		return 1;
	}

    // Creates the camera, used as an abstraction to calculate the view matrix
    Camera * camera = new Camera(vec3(0.0f, 80.0f, 100.0f), vec3(0.0f, 1.0f, 0.0f), -90.0f, -30.0f, 0.4f, 0.2f, &main_window);
    Camera * circlingCamera = new Camera(vec3(0.0f, 80.0f, 100.0f), vec3(0.0f, 1.0f, 0.0f), -90.0f, -30.0f, 0.4f, 0.2f, &main_window);

    Camera * front = new Camera(vec3(0.0f, 20.0f, 30.0f), vec3(0.0f, 1.0f, 0.0f), -90.0f, -6.0f, 0.4f, 0.2f, &main_window);
    Camera * back = new Camera(vec3(0.0f, 20.0f, -50.0f), vec3(0.0f, 1.0f, 0.0f), 90.0f, -6.0f, 0.4f, 0.2f, &main_window);
    Camera * origin = new Camera(vec3(0, 25, 20), vec3(0.0f, 1.0f, 0.0f), -90.0f, 38.6598083f - 90.0f, 0.4f, 0.2f, &main_window);

    Camera * cameras[5] = { camera, front, back, circlingCamera, origin };
    Camera * selectedCamera = cameras[0];

    // Load shader programs
	Shader app_shader(vertex_path, fragment_path);
	Shader shadow_shader(shadow_vertex_path, shadow_fragment_path);
	Shader skybox_shader(skybox_vertex_path, skybox_fragment_path);

	// Init entity renderer and manager, create necessary entities
	SceneRenderer sceneRenderer(app_shader, shadow_shader);

	// Managers
	EntityManager entityManager;
	SpotlightManager spotlightManager;

	// Add spotlights
	Spotlight * mainSpotlight = new Spotlight(vec3(0.7, 0.7, 0.7), vec3(0, 25, 20), vec3(0, -1, -4), 25, 35, 2048, 2);
    Spotlight * ceilingSpotlight = new Spotlight(vec3(1.2 * 0.496, 1.2 * 0.478, 0.1), vec3(0, 73, 30), vec3(0, -4, -5), 5, 10, 2048, 3);
    Spotlight * circlingSpotlight = new Spotlight(vec3(1.0, 0, 1.0), vec3(0, 0, 10), vec3(0, 0, -1), 15, 25, 2048, 4);
    circlingSpotlight->toggleActive();
    ceilingSpotlight->toggleActive();
	spotlightManager.add(mainSpotlight);
	spotlightManager.add(ceilingSpotlight);
	spotlightManager.add(circlingSpotlight);

    AssetLoader loader;

    // Skybox
    const Mesh * skyboxMesh = loader.load_mesh("skybox.obj");
    const Texture * skyboxTexture = loader.load_texture_cube("skybox/skybox");
    TexturedMesh * skybox = new TexturedMesh(skyboxMesh, skyboxTexture);

    // Specifies the alignment requirements for the start of each pixel row in memory. The allowable values are 1 (byte-alignment), 2 (rows aligned to even-numbered bytes), 4 (word-alignment), and 8 (rows start on double-word boundaries).
    // I think we have to use 1 because our data is held in an array of 1 byte unsigned char type
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load textures
    const Texture * floorTexture = loader.load_texture_2d("Floor-Tiles.jpg");
    const Texture * clothTexture = loader.load_texture_2d("Cloth-Texture.jpg");
    const Texture * metalPillarTexture = loader.load_texture_2d("Metal-Pillars.jpg");
    const Texture * metalHolderTexture = loader.load_texture_2d("Metal-Holder.jpg");

    std::vector<const Texture*> slideShow
    {
        loader.load_texture_2d("CN47_Screenshot.png"),
        loader.load_texture_2d("MI26_Screenshot.png"),
        loader.load_texture_2d("SN48_Screenshot.png")
    };
    size_t currentSlideIndex{ 0u };
    const Texture* currentSlide{ slideShow[currentSlideIndex] };
    double slideShowTimer{ 0.0 };

    Entity* floor = (new Entity(new TexturedMesh(loader.load_mesh("Floor.obj"), floorTexture)));
    Entity* floor_back = (new Entity(new TexturedMesh(loader.load_mesh("Floor_back.obj"), floorTexture)));
    Entity* stage = (new Entity(new TexturedMesh(loader.load_mesh("Stage.obj"), clothTexture)));
    Entity* screen = (new Entity(new TexturedMesh(loader.load_mesh("Screen.obj"), currentSlide)));
    Entity* screen_back = (new Entity(new TexturedMesh(loader.load_mesh("Screen_back.obj"), metalHolderTexture)));
    Entity* pillar1 = (new Entity(new TexturedMesh(loader.load_mesh("Pillar1.obj"), metalPillarTexture)));
    Entity* pillar2 = (new Entity(new TexturedMesh(loader.load_mesh("Pillar2.obj"), metalPillarTexture)));
    Entity* pillarAttach1 = (new Entity(new TexturedMesh(loader.load_mesh("Attach1.obj"), metalHolderTexture)));
    Entity* pillarAttach2 = (new Entity(new TexturedMesh(loader.load_mesh("Attach2.obj"), metalHolderTexture)));
    Entity* pillarAttach3 = (new Entity(new TexturedMesh(loader.load_mesh("Attach3.obj"), metalHolderTexture)));
    Entity* pillarAttach4 = (new Entity(new TexturedMesh(loader.load_mesh("Attach4.obj"), metalHolderTexture)));
    EntityGroup* environment = (new EntityGroup())
        ->add(floor_back)
        ->add(stage)
        ->add(screen)
        ->add(screen_back)
        ->add(pillar1)
        ->add(pillar2)
        ->add(pillarAttach1)
        ->add(pillarAttach2)
        ->add(pillarAttach3)
        ->add(pillarAttach4)
        ->translate(vec3(0, 0, 10));

    entityManager.add(environment);
    entityManager.add(floor);

    // The array of models
    EntityGroup * models[6];
    // The selected model
    EntityGroup* selectedModel;

    create_entities(loader, entityManager, models);

    // The default selected model
    selectedModel = models[0];

    // The window's key states
    bool* keys{ main_window.get_keys() };

	// Creates the grid
	Grid grid(glm::vec3(0.f, 0.f, 0.f));

    // Enable depth in our view space
    glEnable(GL_DEPTH_TEST);
    
    // So we can actually see the points in Point polygon mode
    glPointSize(3.f);

    // Hide surfaces facing away from camera
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // Set clear color to white
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // For getting back the control of the mouse during runtime
    bool cursor_enabled = false;

    // Key callback
    bool textureToggle = true;
    main_window.set_key_callback([&app_shader, &selectedModel, &textureToggle, &main_window, &cursor_enabled, &mainSpotlight, &circlingSpotlight, &ceilingSpotlight, &selectedCamera, &cameras, &models](int key, int code, int action, int mode) {
        if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_RELEASE) {
            app_shader.use_shader();
            app_shader.toggle_shadows();
        } else if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
            textureToggle = !textureToggle;
        } else if (key == GLFW_KEY_C && action == GLFW_RELEASE) {
            circlingSpotlight->toggleActive();
        } else if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
            mainSpotlight->toggleActive();
        } else if (key == GLFW_KEY_N && action == GLFW_RELEASE) {
            ceilingSpotlight->toggleActive();
        } else if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
            selectedCamera = cameras[0];
        } else if (key == GLFW_KEY_M && action == GLFW_RELEASE) {
            selectedCamera = cameras[1];
        } else if (key == GLFW_KEY_B && action == GLFW_RELEASE) {
            selectedCamera = cameras[2];
        } else if (key == GLFW_KEY_E && action == GLFW_RELEASE) {
            selectedCamera = cameras[3];
        } else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
            selectedCamera = cameras[4];
        } else if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
            selectedModel = models[0];
        } else if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
            selectedModel = models[1];
        } else if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {
            selectedModel = models[2];
        } else if (key == GLFW_KEY_4 && action == GLFW_RELEASE) {
            selectedModel = models[3];
        } else if (key == GLFW_KEY_5 && action == GLFW_RELEASE) {
            selectedModel = models[4];
        } else if (key == GLFW_KEY_6 && action == GLFW_RELEASE) {
            selectedModel = models[5];
        }
    });

	// Loop until window closed
    GLfloat last_time = 0;
	while (!main_window.should_close())
	{
		// Calculate delta time to minimize speed differences on faster CPUs
		GLfloat now = glfwGetTime();
        GLfloat delta_time = now - last_time;
        slideShowTimer += delta_time;
		last_time = now;

        if (slideShowTimer >= 10.0)
        {
            screen->set_texture(slideShow[currentSlideIndex]);

            // This is for circular iteration through the slide show
            if (++currentSlideIndex >= slideShow.size())
            {
                currentSlideIndex = 0u;
            }

            slideShowTimer = 0.0;
        }

		// Get user input events
		glfwPollEvents();



        if (selectedCamera == camera) {
            camera->key_controls(main_window.get_keys(), delta_time, selectedModel);
            camera->mouse_controls(main_window.get_x_change(), main_window.get_y_change(), main_window.get_mouse_buttons(), delta_time);
        }

        circlingCamera->key_controls_circle(main_window.get_keys(), delta_time, vec3(0, 0, 0), 20.0f, 2.0f);
        circlingSpotlight->setDirection(circlingCamera->getFront());
        circlingSpotlight->setPosition(circlingCamera->getPosition());

        app_shader.use_shader();
        glUniform1i(app_shader.get_use_texture_location(), textureToggle);
        glUniform1i(app_shader.get_use_lighting_location(), true);
        sceneRenderer.render(main_window.get_buffer_width(), main_window.get_buffer_height(), *selectedCamera, entityManager, spotlightManager);

        mat4 projection = selectedCamera->calculate_projection();
        mat4 view = selectedCamera->calculate_view_matrix();
        mat4 model = glm::rotate(mat4(1.0f), glm::radians(-90.0f), vec3(1, 0, 0));

        // Render Skybox
        skybox_shader.use_shader();
        glUniformMatrix4fv(skybox_shader.get_projection_location(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(skybox_shader.get_view_location(), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(skybox_shader.get_model_location(), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(skybox->get_mesh()->get_vao());
        glEnableVertexAttribArray(0);
        skybox->get_texture()->bind_to_unit(0);
        skybox->get_mesh()->render_mesh();
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);

        app_shader.use_shader();
        glUniformMatrix4fv(app_shader.get_projection_location(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(app_shader.get_model_location(), 1, GL_FALSE, glm::value_ptr(mat4(1.0f)));
        glUniform3f(app_shader.get_eye_position_location(),
                    selectedCamera->get_camera_position().x,
                    selectedCamera->get_camera_position().y,
                    selectedCamera->get_camera_position().z);

		// Display the axis lines
        glUniform1i(app_shader.get_use_texture_location(), false);
        glUniform1i(app_shader.get_use_lighting_location(), false);

		// Display the grid
		grid.render();

		// Stop the shader
		glUseProgram(0);

		// Display the newly rendered buffer in the window
		main_window.swap_buffers();

	}

	return 0;
}