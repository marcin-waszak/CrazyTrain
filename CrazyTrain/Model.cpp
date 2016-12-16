#include "Model.h"

glm::mat4 Model::GetModelMatrix() {
	return model_;
}

void Model::SetModelMatrix(glm::mat4 model) {
	model_ = model;
}

void Model::GetUniformLocations() {
	shader_->Use();

	model_location_ = glGetUniformLocation(shader_->GetProgram(), "model");
	view_location_ = glGetUniformLocation(shader_->GetProgram(), "view");
	projection_location_ = glGetUniformLocation(shader_->GetProgram(), "projection");
	object_color_location_ = glGetUniformLocation(shader_->GetProgram(), "objectColor");
	light_color_location_ = glGetUniformLocation(shader_->GetProgram(), "lightColor");
	light_position_location_ = glGetUniformLocation(shader_->GetProgram(), "lightPos");
	view_position_location_ = glGetUniformLocation(shader_->GetProgram(), "viewPos");
}
