#include "LightsManager.h"

LightsManager::LightsManager(Shader* shader, Camera* camera) : light_model_(shader, camera) {

}

void LightsManager::AddPointLight(glm::vec3 position, glm::vec3 color, GLfloat attenuation, GLfloat diffuse, GLfloat specular) {
	point_lights_.push_back({position, color, attenuation, diffuse, specular});
}

/*const */std::vector<LightsManager::PointLight>& LightsManager::GetPointLights() {
	return point_lights_;
}

void LightsManager::Draw() {
	for (auto &light : point_lights_) {
		light_matrix_ = glm::translate(glm::mat4(), light.position);
		light_model_.SetModelMatrix(light_matrix_);
		light_model_.SetColor(light.color);
		light_model_.Draw();
	}
}
