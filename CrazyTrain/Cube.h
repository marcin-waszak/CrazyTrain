#pragma once

#include "Model.h"

class Cube : public Model {
	static GLfloat vertices[];

public:
	Cube();
	~Cube();

	void Draw() const override;

	void AttachMatrices(
		const glm::mat4& view,
		const glm::mat4& projection
	) override;
};
