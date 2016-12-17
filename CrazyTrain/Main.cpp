#include <iostream>
#include <cmath>

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
#include "Camera.h"
#include "Cube.h"
#include "Light.h"

void do_movement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Light attributes
glm::vec3 light_position(1.2f, 1.0f, 2.0f);

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


	Shader shader_cube("basic_lighting.vs", "basic_lighting.frag");
	Shader shader_light("lamp.vs", "lamp.frag");

	Cube cube(&shader_cube, &camera, light_position);
	Cube cube2(&shader_cube, &camera, light_position);
	Light light(&shader_light, &camera);

	cube.SetModelMatrix(glm::mat4()); // BUG !!!!!!!!!!!!!!!!!!!!!!

	glm::mat4 second_model = glm::translate(glm::mat4(), glm::vec3(12.2f, 3.0f, 2.0f));
	cube2.SetModelMatrix(second_model);

	glm::mat4 light_model;
	light_model = glm::translate(light_model, light_position);
	light_model = glm::scale(light_model, glm::vec3(0.2f)); // Make it a smaller cube
	light.SetModelMatrix(light_model);
	
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
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		second_model = glm::rotate(second_model, .02f, glm::vec3(0.f, 1.f, 0.f));
		cube2.SetModelMatrix(second_model);

		cube.Draw();
		cube2.Draw();
		light.Draw();
		
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
}
