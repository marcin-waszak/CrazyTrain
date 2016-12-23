#include "LightsManager.h"

GLfloat LightsManager::LightModel::vertices[] = {
	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	-0.1f, 0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,

	-0.1f, -0.1f, 0.1f,
	0.1f, -0.1f, 0.1f,
	0.1f, 0.1f, 0.1f,
	0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, -0.1f, 0.1f,

	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,

	0.1f, 0.1f, 0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	0.1f, 0.1f, 0.1f,

	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, -0.1f,

	-0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, 0.1f,
	0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f,
};

LightsManager::LightModel::LightModel(Shader* shader, Camera* camera) {
	shader_ = shader;
	camera_ = camera;

	GetUniformLocations();

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

LightsManager::LightModel::~LightModel() {
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
}

void LightsManager::LightModel::Draw() {
	glm::mat4 view_matrix = camera_->GetViewMatrix();
	glm::mat4 projection_matrix = camera_->GetProjectionMatrix();

	shader_->Use();

	glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(model_));
	glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform3fv(color_location_, 1, glm::value_ptr(color_));

	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void LightsManager::LightModel::SetColor(glm::vec3 color) {
	color_ = color;
}

void LightsManager::LightModel::GetUniformLocations() {
	Model::GetUniformLocations();

	color_location_ = glGetUniformLocation(shader_->GetProgram(), "LightColor");
}
