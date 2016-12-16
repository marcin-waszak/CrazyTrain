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

	glm::mat4 model_; // must init !!!!

	GLint model_location;
	GLint view_location;
	GLint projection_location;

	GLint objectColorLoc;
	GLint lightColorLoc;
	GLint lightPosLoc;
	GLint viewPosLoc;

	void GetUniformLocations();// priv

public:
	Shader* shader_; // ????????
	Camera* camera_; // niepotrzebne przy swietle
	glm::vec3 light_position_;

	virtual void Draw() const = 0;
	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 model);
	
};
