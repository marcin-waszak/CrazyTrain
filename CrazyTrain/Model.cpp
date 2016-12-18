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
	normal_matrix_location_ = glGetUniformLocation(shader_->GetProgram(), "normal_matrix");
	object_color_location_ = glGetUniformLocation(shader_->GetProgram(), "objectColor");
	view_position_location_ = glGetUniformLocation(shader_->GetProgram(), "viewPos");
	light_color_location_ = glGetUniformLocation(shader_->GetProgram(), "light.color");
	light_position_location_ = glGetUniformLocation(shader_->GetProgram(), "light.position");
	light_constant_location_ = glGetUniformLocation(shader_->GetProgram(), "light.constant");
	light_linear_location_ = glGetUniformLocation(shader_->GetProgram(), "light.linear");
	light_quadratic_location_ = glGetUniformLocation(shader_->GetProgram(), "light.quadratic");

	light_ambient_location_ = glGetUniformLocation(shader_->GetProgram(), "light.ambient");
	light_difuse_location_ = glGetUniformLocation(shader_->GetProgram(), "light.difuse");
	light_specular_location_ = glGetUniformLocation(shader_->GetProgram(), "light.specular");
}
