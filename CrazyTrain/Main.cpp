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
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool    keys[1024];

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
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
	glfwSetScrollCallback(window, scroll_callback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	Shader shader_cube("basic_lighting.vs", "basic_lighting.frag");
	Shader shader_light("lamp.vs", "lamp.frag");

	Cube cube(&shader_cube, &camera, lightPos);
	Cube cube2(&shader_cube, &camera, lightPos);
	Light light(&shader_light, &camera);

	cube.setModelMatrix(glm::mat4()); // BUG !!!!!!!!!!!!!!!!!!!!!!

	glm::mat4 second_model = glm::translate(glm::mat4(), glm::vec3(12.2f, 3.0f, 2.0f));
	cube2.setModelMatrix(second_model);

	glm::mat4 LightModel;
	LightModel = glm::translate(LightModel, lightPos);
	LightModel = glm::scale(LightModel, glm::vec3(0.2f)); // Make it a smaller cube
	light.setModelMatrix(LightModel);
	
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		do_movement();

		// Create camera transformations
		//view = camera.GetViewMatrix();
		//projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
		// Use cooresponding shader when setting uniforms/drawing objects
		//GLint objectColorLoc = glGetUniformLocation(cube.shader_.GetProgram(), "objectColor");
		//GLint lightColorLoc = glGetUniformLocation(cube.shader_.GetProgram(), "lightColor");
		//GLint lightPosLoc = glGetUniformLocation(cube.shader_.GetProgram(), "lightPos");
		//GLint viewPosLoc = glGetUniformLocation(cube.shader_.GetProgram(), "viewPos");
		//cube.shader_.Use();
		//glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
		//glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		//glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
		cube.Draw();

		//objectColorLoc = glGetUniformLocation(cube2.shader_.GetProgram(), "objectColor");
		//lightColorLoc = glGetUniformLocation(cube2.shader_.GetProgram(), "lightColor");
		//lightPosLoc = glGetUniformLocation(cube2.shader_.GetProgram(), "lightPos");
		//viewPosLoc = glGetUniformLocation(cube2.shader_.GetProgram(), "viewPos");
		//cube2.shader_.Use();
		//glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
		//glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		//glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
		cube2.Draw();


		// Also draw the lamp object, again binding the appropriate shader
		//light.shader_.Use();  // ???


		light.Draw();
		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
