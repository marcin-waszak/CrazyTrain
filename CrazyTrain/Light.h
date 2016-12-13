#pragma once

#include "Model.h"

class Light : public Model {
	static GLfloat vertices[];

public:
	Light();
	~Light();

	void Draw() const override;

	void AttachMatrices(
		const glm::mat4& view,
		const glm::mat4& projection
	) override;
};
