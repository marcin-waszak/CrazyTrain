#pragma once

#include "Model.h"
#include "LightsManager.h"

#include <string>

class CubeModel : public Model {
	static GLfloat vertices[];

public:
	CubeModel(Material* material, Camera* camera, std::vector<LightsManager::PointLight>& plights);
	~CubeModel();

	void Draw() const override;

private:
	void GetUniformLocations();

	std::vector<LightsManager::PointLight>& plights_;

	std::vector<GLint> plight_color_location_;
	std::vector<GLint> plight_position_location_;
	std::vector<GLint> plight_constant_location_;
	std::vector<GLint> plight_linear_location_;
	std::vector<GLint> plight_quadratic_location_;
	std::vector<GLint> plight_ambient_location_;
	std::vector<GLint> plight_diffuse_location_;
	std::vector<GLint> plight_specular_location_;
};
