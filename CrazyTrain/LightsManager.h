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

		void Draw() override;
		void SetColor(glm::vec3 color);
		void GetUniformLocations();

	private:
		GLuint vbo_;
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

	struct SpotLight {
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 color;
		GLfloat attenuation;
		GLfloat diffuse;
		GLfloat specular;
		GLfloat cutoff;
		GLfloat outer_cutoff;
	};

	void AddPointLight(
		glm::vec3 position,
		glm::vec3 color,
		GLfloat attenuation,
		GLfloat diffuse,
		GLfloat specular);

	void AddSpotLight(
		glm::vec3 position,
		glm::vec3 direction,
		glm::vec3 color,
		GLfloat attenuation,
		GLfloat diffuse,
		GLfloat specular,
		GLfloat cutoff,
		GLfloat outer_cutoff);
	/*const */std::vector<PointLight>& GetPointLights();
	/*const */std::vector<SpotLight>& GetSpotLights();

	void Draw();

private:
	std::vector<PointLight> point_lights_;
	std::vector<SpotLight> spot_lights_;
	LightModel light_model_;
	glm::mat4 light_matrix_;
};
