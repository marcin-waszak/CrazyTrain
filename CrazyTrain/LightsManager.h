#pragma once

#include "Model.h"

#include <glm/glm.hpp>

#include <vector>

class LightsManager {
	class LightModel : public Model {
		static GLfloat vertices[];

	public:
		LightModel(Shader* shader, Camera* camera);
		~LightModel();

		void Draw() const override;
		void SetColor(glm::vec3 color);
		void GetUniformLocations();

	private:
		glm::vec3 color_;
		GLint color_location_;
	};

public:
	LightsManager(Shader* shader, Camera* camera);

	struct PointLight {
		glm::vec3 position;
		glm::vec3 color;
		GLfloat attenuation;

		GLfloat diffuse;
		GLfloat specular;
	};

	void AddPointLight(
		glm::vec3 position,
		glm::vec3 color,
		GLfloat attenuation,
		GLfloat diffuse,
		GLfloat specular);
	/*const */std::vector<LightsManager::PointLight>&  GetPointLights();

	void Draw();

private:
	std::vector<PointLight> point_lights_;
	LightModel light_model_;
	glm::mat4 light_matrix_;
};
