#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Input.h"
#include "Shader.h"
#include "LightsManager.h"
#include "Material.h"
#include "Camera.h"
#include "CubeModel.h"

void do_movement();

// Window dimensions
const GLuint WIDTH = 1600, HEIGHT = 900;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Light attributes
//glm::vec3 light_position(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat delta_time = 0.0f;  // Time between current frame and last frame
GLfloat last_frame = 0.0f;  // Time of last frame

int main() {
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Crazy Train", nullptr, nullptr);
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

	Input* input = Input::getInstance();
	input->Initialize(&camera);

	Shader shader_cube(
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\basic_lighting.vs",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\basic_lighting.frag");
	Shader shader_light(
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\lamp.vs",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\lamp.frag");

	Material box_material(&shader_cube, 32.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\container2.png",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\container2_specular.png");

	LightsManager lights(&shader_light, &camera);
	lights.AddPointLight(glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.032f, 0.8f, 1.0f);
	lights.AddPointLight(glm::vec3(10.f, 10.f, 10.f), glm::vec3(1.f, 0.f, 0.f), 0.016f, 0.8f, 1.0f);
	lights.AddPointLight(glm::vec3(-10.f, -10.f, 10.f), glm::vec3(0.f, 1.f, 0.f), 0.016f, 0.8f, 1.0f);
	lights.AddPointLight(glm::vec3(10.f, -10.f, -10.f), glm::vec3(0.f, 0.f, 1.f), 0.016f, 0.8f, 1.0f);

	// delete it !!!!

	// Positions of the point lights
	//glm::vec3 pointLightPositions[] = {
	//	glm::vec3(0.7f,  0.2f,  2.0f),
	//	//glm::vec3(2.3f, -3.3f, -4.0f),
	//	//glm::vec3(-4.0f,  2.0f, -12.0f),
	//	//glm::vec3(0.0f,  0.0f, -3.0f)
	//};

	// !!!!!!!!!!

	srand(time(nullptr));

	std::vector<CubeModel*> cubes;
	for (int i = 0; i < 1000; ++i)
		cubes.push_back(new CubeModel(&box_material, &camera, lights.GetPointLights()));

	int range = 40;

	for (auto &cube : cubes) {
		glm::mat4 trans = glm::translate(glm::mat4(),
			glm::vec3(-range/2 + rand() % range, -range / 2 + rand() % range, -range / 2 + rand() % range));
		glm::mat4 rot = glm::rotate(glm::mat4(), 45.f, glm::vec3(0.f, 1.f, 0.0f));
		glm::mat4 result = trans *rot;
		cube->SetModelMatrix(result);
	}

//	Light light(&shader_light, &camera);

	glm::mat4 light_model;
	//light_model = glm::translate(light_model, light_position);
	//light_model = glm::scale(light_model, glm::vec3(0.2f)); // Make it a smaller cube
	//light.SetModelMatrix(light_model);
	
	// Game loop
	while (!glfwWindowShouldClose(window)) {
		// Calculate deltatime of current frame
		GLfloat current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		// Check if any events have been activiated (key pressed, mouse moved etc.)
		// and call corresponding response functions
		glfwPollEvents();
		do_movement();

		// Clear the colorbuffer
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		//glClearColor(0.01f, 0.01f, 0.03f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lights.Draw();

		for (auto &cube : cubes)
			cube->Draw();

		//second_model = glm::rotate(second_model, .02f, glm::vec3(0.f, 1.f, 0.f));
		//cube2.SetModelMatrix(second_model);

		//light.Draw();

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

void do_movement() {
	Input* input = Input::getInstance();

	// Camera controls
	if (input->IsPressed(GLFW_KEY_W))
		camera.ProcessKeyboard(FORWARD, delta_time);
	if (input->IsPressed(GLFW_KEY_S))
		camera.ProcessKeyboard(BACKWARD, delta_time);
	if (input->IsPressed(GLFW_KEY_A))
		camera.ProcessKeyboard(LEFT, delta_time);
	if (input->IsPressed(GLFW_KEY_D))
		camera.ProcessKeyboard(RIGHT, delta_time);
	if (input->IsPressed(GLFW_KEY_SPACE))
		camera.ProcessKeyboard(UP, delta_time);
	if (input->IsPressed(GLFW_KEY_C))
		camera.ProcessKeyboard(DOWN, delta_time);

		camera.Move(delta_time);
}
