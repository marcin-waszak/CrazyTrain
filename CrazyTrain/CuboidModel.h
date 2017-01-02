#pragma once

#include "Model.h"
#include "LightsManager.h"

class CuboidModel : public Model {
	GLfloat vertices_[108];
	GLfloat normals_[108];
//	GLfloat texture_[72];
public:
	CuboidModel(glm::vec3 dimensions,
		Material* material,
		Camera* camera,
		LightsManager* lights_manager);

	~CuboidModel();
	void Draw() override;

private:
	void GetUniformLocations();

	GLuint vbo_vertices_;
	GLuint vbo_normals_;
	GLuint vbo_texture_;
	LightsManager* lights_manager_;

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
