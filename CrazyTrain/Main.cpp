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
#include "Shader.h"
#include "Camera.h"
#include "Cube.h"
#include "Light.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double x_position, double y_position);
//void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
void do_movement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat last_x = WIDTH / 2.0;
GLfloat last_y = HEIGHT / 2.0;
bool keys[1024];

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
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
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

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement() {
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, delta_time);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, delta_time);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, delta_time);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, delta_time);
}

bool first_mouse_ = true;
void mouse_callback(GLFWwindow* window, double x_position, double y_position) {
	if (first_mouse_) {
		last_x = x_position;
		last_y = y_position;
		first_mouse_ = false;
	}

	GLfloat x_offset = x_position - last_x;
	GLfloat y_offset = last_y - y_position;  // Reversed since y-coordinates go from bottom to left

	last_x = x_position;
	last_y = y_position;

	camera.ProcessMouseMovement(x_offset, y_offset);
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
	camera.ProcessMouseScroll(y_offset);
}
