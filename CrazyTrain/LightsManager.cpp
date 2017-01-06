#include "LightsManager.h"

LightsManager::LightsManager(Shader* shader, Camera* camera) : light_model_(shader, camera) {

}

void LightsManager::AddPointLight(glm::vec3 position, glm::vec3 color, GLfloat attenuation, GLfloat diffuse, GLfloat specular) {
	point_lights_.push_back({position, color, attenuation, diffuse, specular});
}

void LightsManager::AddSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, GLfloat attenuation, GLfloat diffuse, GLfloat specular, GLfloat cutoff, GLfloat outer_cutoff) {
	spot_lights_.push_back({position, direction, color, attenuation, diffuse, specular, cutoff, outer_cutoff});
}

std::vector<LightsManager::PointLight>& LightsManager::GetPointLights() {
	return point_lights_;
}

std::vector<LightsManager::SpotLight>& LightsManager::GetSpotLights() {
	return spot_lights_;
}

void LightsManager::Draw() {
	for (auto &light : point_lights_) {
		light_model_.SetInitTranslation(light.position);
		light_model_.SetColor(light.color);
		light_model_.Draw();
	}

	for (auto &light : spot_lights_) {
		light_model_.SetInitTranslation(light.position);
		light_model_.SetColor(light.color);
		light_model_.Draw();
	}
}
