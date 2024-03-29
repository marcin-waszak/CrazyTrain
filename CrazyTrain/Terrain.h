#pragma once

#include "Model.h"
#include "LightsManager.h"

class Terrain : public Model {
	GLuint vbo_;
	static GLfloat vertices[];

public:
	Terrain(Material* material, Camera* camera, std::vector<LightsManager::PointLight>& plights, std::vector<LightsManager::SpotLight>& slights);
	~Terrain();

	void Draw() override;

private:
	void GetUniformLocations();

	std::vector<LightsManager::PointLight>& plights_;
	std::vector<LightsManager::SpotLight>& slights_;

	std::vector<GLint> plight_color_location_;
	std::vector<GLint> plight_position_location_;
	std::vector<GLint> plight_constant_location_;
	std::vector<GLint> plight_linear_location_;
	std::vector<GLint> plight_quadratic_location_;
	std::vector<GLint> plight_ambient_location_;
	std::vector<GLint> plight_diffuse_location_;
	std::vector<GLint> plight_specular_location_;

	std::vector<GLint> slight_color_location_;
	std::vector<GLint> slight_position_location_;
	std::vector<GLint> slight_direction_location_;
	std::vector<GLint> slight_constant_location_;
	std::vector<GLint> slight_linear_location_;
	std::vector<GLint> slight_quadratic_location_;
	std::vector<GLint> slight_ambient_location_;
	std::vector<GLint> slight_diffuse_location_;
	std::vector<GLint> slight_specular_location_;
	std::vector<GLint> slight_cutoff_location_;
	std::vector<GLint> slight_outer_cutoff_location_;
};

