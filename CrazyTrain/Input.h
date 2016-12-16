#pragma once

#include "Camera.h"

// GLFW
#include <GLFW/glfw3.h>

class Input {
public:
	static void Initialize(Camera* camera);
	static Input* getInstance();
	// Function prototypes
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseCallback(GLFWwindow* window, double x_position, double y_position);
	static void ScrollCallback(GLFWwindow* window, double x_offset, double y_offset);

	bool IsPressed(GLuint key) const;

private:
	bool keys_[1024];
	Camera* camera_;
	GLfloat last_x_ = 800 / 2.0;
	GLfloat last_y_ = 600 / 2.0;

	Input();

public:
	Input(Input const&) = delete;
	void operator=(Input const&) = delete;
};
