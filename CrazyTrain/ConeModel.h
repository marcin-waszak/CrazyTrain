#pragma once

#include "Model.h"
#include "LightsManager.h"

class ConeModel : public Model {
	static const int CONE_SEGMENTS = 16;
	GLfloat vertices_[2 * 2 * 3 * 3 * CONE_SEGMENTS];
	GLfloat normals_[2 * 2 * 3 * 3 * CONE_SEGMENTS];
	//	GLfloat texture_[72];
public:
	ConeModel(
		GLfloat radius_a,
		GLfloat radius_b,
		GLfloat height,
		Material* material,
		Camera* camera,
		LightsManager* lights_manager);

	~ConeModel();
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
