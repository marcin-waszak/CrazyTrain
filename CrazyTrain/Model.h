#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Model {
protected:
	GLuint VAO;
	GLuint VBO;

	

	glm::mat4 model_;

	GLint model_location;
	GLint view_location;
	GLint projection_location;

	const float* model_ptr_;
	const float* view_ptr_;
	const float* projection_ptr_;

public:
	Shader shader_; // ????????

	Model();

	virtual void Draw() const = 0;

	virtual void AttachMatrices(
		const glm::mat4& view,
		const glm::mat4& projection
	) = 0;

	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 model);
	void GetUniformLocations();
};
