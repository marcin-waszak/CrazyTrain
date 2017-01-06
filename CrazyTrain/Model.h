#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Camera.h"

class Model {
protected:
	GLuint vao_;

	Shader* shader_;
	Material* material_;
	Camera* camera_; // unnecessary in light class

	glm::mat4 model_;

	glm::mat4 init_rotation_;
	glm::mat4 init_translation_;
	glm::mat4 rotation_;
	glm::mat4 translation_;

	GLint model_location_;
	GLint view_location_;
	GLint projection_location_;
	GLint normal_matrix_location_;
	GLint view_position_location_;

	void GetUniformLocations();

public:
	virtual void Draw() = 0;
	glm::mat4 GetModelMatrix();
	void SetInitRotation(GLfloat angle, glm::vec3 axis);
	void SetInitTranslation(glm::vec3 translation);
	void SetRotation(GLfloat angle, glm::vec3 axis);
	void SetTranslation(glm::vec3 translation);
	void UpdateModelMatrix();
};
