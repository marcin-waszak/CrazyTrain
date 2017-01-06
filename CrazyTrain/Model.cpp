#include "Model.h"

glm::mat4 Model::GetModelMatrix() {
	return model_;
}

void Model::SetInitRotation(GLfloat angle, glm::vec3 axis) {
	init_rotation_ = glm::rotate(glm::mat4(), glm::radians(angle), axis);
	UpdateModelMatrix();
}

void Model::SetInitTranslation(glm::vec3 translation) {
	init_translation_ = glm::translate(glm::mat4(), translation);
	UpdateModelMatrix();
}

void Model::SetRotation(GLfloat angle, glm::vec3 axis) {
	rotation_ = glm::rotate(glm::mat4(), glm::radians(angle), axis);
}

void Model::SetTranslation(glm::vec3 translation) {
	translation_ = glm::translate(glm::mat4(), translation);
}

void Model::UpdateModelMatrix() {
	// correct order: TRS
	model_ = translation_ * init_translation_ * rotation_ * init_rotation_;
}

void Model::GetUniformLocations() {
	shader_->Use();

	model_location_ = glGetUniformLocation(shader_->GetProgram(), "model");
	view_location_ = glGetUniformLocation(shader_->GetProgram(), "view");
	projection_location_ = glGetUniformLocation(shader_->GetProgram(), "projection");
	normal_matrix_location_ = glGetUniformLocation(shader_->GetProgram(), "normal_matrix");
	view_position_location_ = glGetUniformLocation(shader_->GetProgram(), "viewPos");
}
