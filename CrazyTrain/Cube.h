#pragma once

#include "Model.h"

class Cube : public Model {
	static GLfloat vertices[];

public:
	Cube(Material* material, Camera* camera, glm::vec3 light_position);
	~Cube();

	void Draw() const override;
};
