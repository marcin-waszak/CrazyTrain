#include "Input.h"

void Input::Initialize(Camera * camera) {
	getInstance()->camera_ = camera;
}

Input* Input::getInstance() {
	static Input instance;
	return &instance;
}

Input::Input() {

}

// Is called whenever a key is pressed/released via GLFW
void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			getInstance()->keys_[key] = true;
		else if (action == GLFW_RELEASE)
			getInstance()->keys_[key] = false;
	}
}

bool first_mouse_ = true;
void Input::MouseCallback(GLFWwindow* window, double x_position, double y_position) {
	if (first_mouse_) {
		getInstance()->last_x_ = x_position;
		getInstance()->last_y_ = y_position;
		first_mouse_ = false;
	}

	GLfloat x_offset = x_position - getInstance()->last_x_;
	GLfloat y_offset = getInstance()->last_y_ - y_position;
	// Reversed since y-coordinates go from bottom to left

	getInstance()->last_x_ = x_position;
	getInstance()->last_y_ = y_position;

	getInstance()->camera_->ProcessMouseMovement(x_offset, y_offset);
}

void Input::ScrollCallback(GLFWwindow* window, double x_offset, double y_offset) {
	getInstance()->camera_->ProcessMouseScroll(y_offset);
}

bool Input::IsPressed(GLuint key) const {
	return keys_[key];
}
