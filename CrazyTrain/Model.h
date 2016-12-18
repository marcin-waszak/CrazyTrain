#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

class Model {
protected:
	GLuint vao_;
	GLuint vbo_;

	Shader* shader_;
	Camera* camera_; // unnecessary in light class
	glm::vec3 light_position_;

	glm::mat4 model_; // must init !!!!

	GLint model_location_;
	GLint view_location_;
	GLint projection_location_;
	GLint normal_matrix_location_;
	GLint object_color_location_;
	GLint light_color_location_;
	GLint light_position_location_;
	GLint light_constant_location_;
	GLint light_linear_location_;
	GLint light_quadratic_location_;
	GLint view_position_location_;

	GLint light_ambient_location_;
	GLint light_diffuse_location_;
	GLint light_specular_location_;



	void GetUniformLocations();

public:
	virtual void Draw() const = 0;
	glm::mat4 GetModelMatrix();
	void SetModelMatrix(glm::mat4 model);
};
