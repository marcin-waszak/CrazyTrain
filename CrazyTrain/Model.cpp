#include "Model.h"

Model::Model() {
	
}

glm::mat4 Model::getModelMatrix() {
	return model_;
}

void Model::setModelMatrix(glm::mat4 model) {
	model_ = model;
	model_ptr_ = glm::value_ptr(model_);
}

void Model::GetUniformLocations() {
	// Get the uniform locations
	model_location = glGetUniformLocation(shader_.GetProgram(), "model");
	view_location = glGetUniformLocation(shader_.GetProgram(), "view");
	projection_location = glGetUniformLocation(shader_.GetProgram(), "projection");
}
