#pragma once

#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Skybox : public Model {
	static GLfloat vertices[];

public:
	Skybox(Material* material, Camera* camera);
	~Skybox();
	void Draw() override;
};
