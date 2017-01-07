#include "Core.h"

Core::Core() : camera_(glm::vec3(0.0f, 2.0f, 3.0f)) {
	input_ = Input::getInstance();
	input_->Initialize(&camera_);
}


Core::~Core() {
}

void Core::Start() {
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Crazy Train", glfwGetPrimaryMonitor(), nullptr);
	//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Crazy Train", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Set the required callback functions
	glfwSetKeyCallback(window, Input::KeyCallback);
	glfwSetCursorPosCallback(window, Input::MouseCallback);
	//	glfwSetScrollCallback(window, scroll_callback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach
	// to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	Shader shader_standard(
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\standard.vs",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\standard.frag");
	Shader shader_nonshading(
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\nonshading.vs",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\nonshading.frag");

	Material box_material(&shader_standard, 32.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\container2.png",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\container2_specular.png");

	Material grass_material(&shader_standard, 32.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\master_grass_dirt3.png");

	Shader shader_sky(
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\sky.vs",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\sky.frag");
	Material sky_material(&shader_sky, 0.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\nightsky3.jpg");

	LightsManager lights(&shader_nonshading, &camera_);
	lights.AddPointLight(glm::vec3(0.7f, 5.2f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.016f, 0.8f, 1.0f);
	lights.AddPointLight(glm::vec3(30.f, 5.2f, 30.f), glm::vec3(1.f, 0.f, 0.f), 0.016f, 0.8f, 1.0f);
	lights.AddPointLight(glm::vec3(-10.f, 5.2f, 16.f), glm::vec3(0.f, 1.f, 0.f), 0.016f, 0.8f, 1.0f);
	lights.AddPointLight(glm::vec3(10.f, 5.2f, -10.f), glm::vec3(0.f, 0.f, 1.f), 0.0016f, 0.8f, 1.0f);
	lights.AddPointLight(glm::vec3(10.f, 5.2f, 16.f), glm::vec3(1.f, .6f, 0.f), 0.016f, 0.8f, 1.0f);
	lights.AddPointLight(glm::vec3(5.f, 2.4f, 42.f), glm::vec3(1.f, 1.f, 1.f), 0.016f, 0.8f, 1.0f);
	lights.AddSpotLight(glm::vec3(-10.f, 5.2f, -10.f), glm::vec3(0.5f, -0.25f, -0.5f), glm::vec3(1.0f, 0.8f, 0.5f), 0.002f, 0.8f, 1.0f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));

	srand(time(nullptr));

	Skybox skybox(&sky_material, &camera_);
	Terrain terrain(&grass_material, &camera_, lights.GetPointLights(), lights.GetSpotLights());

	std::vector<CuboidModel*> cubes;
	for (int i = 0; i < 200; ++i)
		cubes.push_back(new CuboidModel(glm::vec3(1.f, 1.f, 1.f), &box_material, &camera_, &lights));

	int range = 70;

	for (auto &cube : cubes) {
		glm::vec3 trans = glm::vec3(range / 8 + rand() % (range / 2), rand() % 3, -range / 2 + rand() % range);;
		cube->SetInitTranslation(trans);
	}

	RailsAssemly rails(&camera_, &lights, &shader_standard);
	TrainAssembly train(&camera_, &lights, &shader_standard);

	glm::mat4 light_model;

	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Calculate deltatime of current frame
		GLfloat current_frame = glfwGetTime();
		delta_time_ = current_frame - last_frame_;
		last_frame_ = current_frame;

		// Check if any events have been activiated (key pressed, mouse moved etc.)
		// and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox.Draw();
		lights.Draw();
		terrain.Draw();
		rails.Draw();
		train.Draw();

		for (auto &cube : cubes)
			cube->Draw();

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

void Core::DoMovement() {
	Input* input = Input::getInstance();

	// Camera controls
	if (input->IsPressed(GLFW_KEY_W))
		camera_.ProcessKeyboard(FORWARD, delta_time_);
	if (input->IsPressed(GLFW_KEY_S))
		camera_.ProcessKeyboard(BACKWARD, delta_time_);
	if (input->IsPressed(GLFW_KEY_A))
		camera_.ProcessKeyboard(LEFT, delta_time_);
	if (input->IsPressed(GLFW_KEY_D))
		camera_.ProcessKeyboard(RIGHT, delta_time_);
	if (input->IsPressed(GLFW_KEY_SPACE))
		camera_.ProcessKeyboard(UP, delta_time_);
	if (input->IsPressed(GLFW_KEY_C))
		camera_.ProcessKeyboard(DOWN, delta_time_);

	camera_.Move(delta_time_);
}
