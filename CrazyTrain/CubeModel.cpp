#include "CubeModel.h"

GLfloat CubeModel::vertices[] = {
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

CubeModel::CubeModel(Material* material, Camera* camera, std::vector<LightsManager::PointLight>& plights, std::vector<LightsManager::SpotLight>& slights) : plights_(plights), slights_(slights) {
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

CubeModel::~CubeModel() {
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
}

void CubeModel::Draw() {
	glm::mat4 view_matrix = camera_->GetViewMatrix();
	glm::mat4 projection_matrix = camera_->GetProjectionMatrix();
	glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_));

	material_->Use();

	glUniform3fv(view_position_location_, 1, glm::value_ptr(camera_->position_));

	// Create camera transformations
	glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(model_));
	glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	glUniformMatrix3fv(normal_matrix_location_, 1, GL_FALSE, glm::value_ptr(normal_matrix));

	// Set pointlights properties
	for (size_t i = 0; i < plights_.size(); ++i) {
		glUniform3fv(plight_color_location_[i], 1, glm::value_ptr(plights_[i].color));
		glUniform3fv(plight_position_location_[i], 1, glm::value_ptr(plights_[i].position));
		glUniform1f(plight_constant_location_[i], 1.f);
		glUniform1f(plight_linear_location_[i], 0.f);
		glUniform1f(plight_quadratic_location_[i], plights_[i].attenuation);
		glUniform1f(plight_ambient_location_[i], 0.03f);
		glUniform1f(plight_diffuse_location_[i], plights_[i].diffuse);
		glUniform1f(plight_specular_location_[i], plights_[i].specular);
	}

	// Set spotlights properties
	for (size_t i = 0; i < slights_.size(); ++i) {
		glUniform3fv(slight_color_location_[i], 1, glm::value_ptr(slights_[i].color));
		glUniform3fv(slight_position_location_[i], 1, glm::value_ptr(slights_[i].position));
		glUniform3fv(slight_direction_location_[i], 1, glm::value_ptr(slights_[i].direction));
		glUniform1f(slight_constant_location_[i], 1.f);
		glUniform1f(slight_linear_location_[i], 0.f);
		glUniform1f(slight_quadratic_location_[i], slights_[i].attenuation);
		glUniform1f(slight_ambient_location_[i], 0.03f);
		glUniform1f(slight_diffuse_location_[i], slights_[i].diffuse);
		glUniform1f(slight_specular_location_[i], slights_[i].specular);
		glUniform1f(slight_cutoff_location_[i], slights_[i].cutoff);
		glUniform1f(slight_outer_cutoff_location_[i], slights_[i].outer_cutoff);
	}

	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void CubeModel::GetUniformLocations() {
	Model::GetUniformLocations();

	char buffer[64];
	GLint location;

	for (size_t i = 0; i < plights_.size(); ++i) {
		snprintf(buffer, sizeof(buffer), "pointLights[%zu].color", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_color_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].position", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_position_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].constant", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_constant_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].linear", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_linear_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].quadratic", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_quadratic_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].ambient", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_ambient_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].diffuse", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_diffuse_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].specular", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_specular_location_.push_back(location);
	}

	for (size_t i = 0; i < slights_.size(); ++i) {
		snprintf(buffer, sizeof(buffer), "spotLights[%zu].color", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_color_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].position", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_position_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].direction", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_direction_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].constant", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_constant_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].linear", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_linear_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].quadratic", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_quadratic_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].ambient", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_ambient_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].diffuse", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_diffuse_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].specular", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_specular_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].cutoff", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_cutoff_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].outer_cutoff", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_outer_cutoff_location_.push_back(location);
	}
}
