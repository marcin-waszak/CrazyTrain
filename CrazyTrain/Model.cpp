#include "Model.h"

glm::mat4 Model::getModelMatrix() {
	return model_;
}

void Model::setModelMatrix(glm::mat4 model) {
	model_ = model;
}

void Model::GetUniformLocations() {
	shader_->Use();

	// Get the uniform locations
	model_location = glGetUniformLocation(shader_->GetProgram(), "model");
	view_location = glGetUniformLocation(shader_->GetProgram(), "view");
	projection_location = glGetUniformLocation(shader_->GetProgram(), "projection");

	objectColorLoc = glGetUniformLocation(shader_->GetProgram(), "objectColor");
	lightColorLoc = glGetUniformLocation(shader_->GetProgram(), "lightColor");
	lightPosLoc = glGetUniformLocation(shader_->GetProgram(), "lightPos");
	viewPosLoc = glGetUniformLocation(shader_->GetProgram(), "viewPos");
}
