#include "Skybox.h"

GLfloat Skybox::vertices[] = {
	// Positions         // Texture Coords
	-0.5f, -0.5f, -0.5f, 0.0f,  0.0f,
	0.5f, -0.5f, -0.5f, 4.f,  0.0f,
	0.5f,  0.5f, -0.5f, 4.f,  4.f,
	0.5f,  0.5f, -0.5f, 4.f,  4.f,
	-0.5f,  0.5f, -0.5f, 0.0f,  4.f,
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,   4.f,  0.0f,
	0.5f,  0.5f,  0.5f,  4.f,  4.f,
	0.5f,  0.5f,  0.5f,  4.f,  4.f,
	-0.5f,  0.5f,  0.5f,  0.0f,  4.f,
	-0.5f, -0.5f,  0.5f, 0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, 4.f,  0.0f,
	-0.5f,  0.5f, -0.5f,4.f,  4.f,
	-0.5f, -0.5f, -0.5f,  0.0f,  4.f,
	-0.5f, -0.5f, -0.5f, 0.0f,  4.f,
	-0.5f, -0.5f,  0.5f, 0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, 4.f,  0.0f,

	0.5f,  0.5f,  0.5f,  4.f,  0.0f,
	0.5f,  0.5f, -0.5f,  4.f,  4.f,
	0.5f, -0.5f, -0.5f,  0.0f,  4.f,
	0.5f, -0.5f, -0.5f,  0.0f,  4.f,
	0.5f, -0.5f,  0.5f, 0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  4.f,  0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f,  4.f,
	0.5f, -0.5f, -0.5f,  4.f,  4.f,
	0.5f, -0.5f,  0.5f,  4.f,  0.0f,
	0.5f, -0.5f,  0.5f,  4.f,  0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  4.f,

	-0.5f,  0.5f, -0.5f, 0.0f,  4.f,
	0.5f,  0.5f, -0.5f,  4.f,  4.f,
	0.5f,  0.5f,  0.5f, 4.f,  0.0f,
	0.5f,  0.5f,  0.5f,   4.f,  0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  4.f
};

Skybox::Skybox(Material* material, Camera* camera) {
	material_ = material;
	shader_ = material_->GetShader();
	camera_ = camera;

	GetUniformLocations();

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Skybox::~Skybox() {
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
}

void Skybox::Draw() {
	glm::mat4 view_matrix = camera_->GetViewMatrix();
	glm::mat4 projection_matrix = camera_->GetProjectionMatrix();

	material_->Use();

	model_ = glm::translate(glm::mat4(), camera_->GetPosition());

	glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(model_));
	glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(projection_matrix));

//	glUniform3fv(color_location_, 1, glm::value_ptr(color_));

	glBindVertexArray(vao_);
	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glEnable(GL_DEPTH_TEST);
	glBindVertexArray(0);
}
