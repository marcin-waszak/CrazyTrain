#include "Cube.h"

GLfloat Cube::vertices[] = {
	// Positions          // Normals           // Texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

Cube::Cube(Shader* shader, Camera* camera, glm::vec3 light_position) {
	shader_ = shader;
	camera_ = camera;
	light_position_ = light_position;

	GetUniformLocations();

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Cube::~Cube() {
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
}

void Cube::Draw() const {
	glm::mat4 view_matrix = camera_->GetViewMatrix();
	glm::mat4 projection_matrix = camera_->GetProjectionMatrix();
	glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_));


	shader_->Use();

//	glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(model_));
//	glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(view_matrix));
//	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(projection_matrix));
//	glUniformMatrix3fv(normal_matrix_location_, 1, GL_FALSE, glm::value_ptr(normal_matrix));
//	glUniform3f(object_color_location_, 1.0f, 0.5f, 0.81f);
//	glUniform3f(light_color_location_, 1.0f, 1.0f, 1.0f);
//	glUniform3fv(light_position_location_, 1, glm::value_ptr(light_position_));
//	glUniform3fv(view_position_location_, 1, glm::value_ptr(camera_->position_));
//	glUniform1f(light_constant_location_, 1.0f);
////	glUniform1f(light_linear_location_, 0.09);
//	glUniform1f(light_linear_location_, 0.00);
////	glUniform1f(light_quadratic_location_, 0.032);
//	glUniform1f(light_quadratic_location_, 0.004);



	glUniform3fv(light_position_location_, 1, glm::value_ptr(light_position_));
	glUniform3fv(view_position_location_, 1, glm::value_ptr(camera_->position_));
	// Set lights properties
	glUniform3f(light_ambient_location_, 0.2f, 0.2f, 0.2f);
	glUniform3f(light_difuse_location_, 0.5f, 0.5f, 0.5f);
	glUniform3f(light_specular_location_, 1.0f, 1.0f, 1.0f);
	glUniform1f(light_constant_location_, 1.0f);
	//	glUniform1f(light_linear_location_, 0.09);
	glUniform1f(light_linear_location_, 0.00);
	//	glUniform1f(light_quadratic_location_, 0.032);
	glUniform1f(light_quadratic_location_, 0.002);
	// Create camera transformations
	glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(model_));
	glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	glUniformMatrix3fv(normal_matrix_location_, 1, GL_FALSE, glm::value_ptr(normal_matrix));



	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
