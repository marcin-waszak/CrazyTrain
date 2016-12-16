#pragma once

#include "Model.h"

class Light : public Model {
	static GLfloat vertices[];

public:
	Light(Shader* shader, Camera* camera);
	~Light();

	void Draw() const override;
};
