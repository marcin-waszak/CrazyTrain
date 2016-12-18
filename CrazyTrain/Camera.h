#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 16.5f;
const GLfloat SENSITIVTY = 0.5f;
const GLfloat ZOOM = 45.0f;

extern const GLuint WIDTH, HEIGHT; // temporary solution !

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
	// Camera Attributes
	glm::vec3 position_;
	glm::vec3 front_;
	glm::vec3 up_;
	glm::vec3 right_;
	glm::vec3 world_up_;
	// Eular Angles
	GLfloat yaw_;
	GLfloat pitch_;
	// Camera options
	GLfloat movement_speed_;
	GLfloat mouse_sensitivity_;
	GLfloat zoom_;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		   GLfloat yaw = YAW, GLfloat pitch = PITCH) {
		front_ = glm::vec3(0.0f, 0.0f, -1.0f);
		movement_speed_ = SPEED;
		mouse_sensitivity_ = SENSITIVTY;
		zoom_ = ZOOM;

		position_ = position;
		world_up_ = up;
		yaw_ = yaw;
		pitch_ = pitch;
		UpdateCameraVectors();
	}

	Camera(GLfloat position_x,
		   GLfloat position_y,
		   GLfloat position_z,
		   GLfloat up_x,
		   GLfloat up_y,
		   GLfloat up_z,
		   GLfloat yaw,
		   GLfloat pitch) {
		front_ = glm::vec3(0.0f, 0.0f, -1.0f);
		movement_speed_ = SPEED;
		mouse_sensitivity_ = SENSITIVTY;
		zoom_ = ZOOM;

		position_ = glm::vec3(position_x, position_y, position_z);
		world_up_ = glm::vec3(up_x, up_y, up_z);
		yaw_ = yaw;
		pitch_ = pitch;
		UpdateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(position_, position_ + front_, up_);
	}

	glm::mat4 GetProjectionMatrix() {
		return glm::perspective(zoom_, (GLfloat)WIDTH / HEIGHT, 0.1f, 1000.0f);
	}

	void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime) {
		GLfloat velocity = movement_speed_ * deltaTime;
		if (direction == FORWARD)
			position_ += front_ * velocity;
		if (direction == BACKWARD)
			position_ -= front_ * velocity;
		if (direction == LEFT)
			position_ -= right_ * velocity;
		if (direction == RIGHT)
			position_ += right_ * velocity;
		if (direction == UP)
			position_ += glm::vec3(0.f, 1.f, 0.f) * velocity * .5f;
		if (direction == DOWN)
			position_ -= glm::vec3(0.f, 1.f, 0.f) * velocity * .5f;
	}

	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true) {
		xoffset *= mouse_sensitivity_;
		yoffset *= mouse_sensitivity_;

		yaw_ += xoffset;
		pitch_ += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch) {
			if (pitch_ > 89.0f)
				pitch_ = 89.0f;
			if (pitch_ < -89.0f)
				pitch_ = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		UpdateCameraVectors();
	}

	void ProcessMouseScroll(GLfloat y_offset) {
		if (zoom_ >= 1.0f && zoom_ <= 45.0f)
			zoom_ -= y_offset;
		if (zoom_ <= 1.0f)
			zoom_ = 1.0f;
		if (zoom_ >= 45.0f)
			zoom_ = 45.0f;
	}

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void UpdateCameraVectors() {
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front.y = sin(glm::radians(pitch_));
		front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front_ = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		// Normalize the vectors, because their length gets closer to 0 the more you look up or down
		// which results in slower movement.
		right_ = glm::normalize(glm::cross(front_, world_up_));
		up_ = glm::normalize(glm::cross(right_, front_));
	}
};
