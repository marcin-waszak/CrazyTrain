#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Camera.h"

class Model {
protected:
	GLuint vao_;
	GLuint vbo_;

	Shader* shader_;
	Material* material_;
	Camera* camera_; // unnecessary in light class

	glm::mat4 model_; // must init !!!!

	GLint model_location_;
	GLint view_location_;
	GLint projection_location_;
	GLint normal_matrix_location_;
	GLint view_position_location_;

	void GetUniformLocations();

public:
	virtual void Draw() = 0;
	glm::mat4 GetModelMatrix();
	void SetModelMatrix(glm::mat4 model);
};
