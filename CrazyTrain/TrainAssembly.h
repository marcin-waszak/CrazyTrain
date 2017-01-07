#pragma once
#include "Material.h"
#include "CuboidModel.h"
#include "ConeModel.h"

class TrainAssembly {
	Shader shader_cube_;
	Material box_material_;
	glm::vec3 translation_;

	glm::vec3 position_;

	ConeModel wheel1_;
	ConeModel wheel2_;
	ConeModel wheel3_;
	ConeModel wheel4_;

	CuboidModel connecting_rod1_;
	CuboidModel connecting_rod2_;

	CuboidModel platform_;

public:
	TrainAssembly(Camera* camera, LightsManager* lights_manager);
	~TrainAssembly();

	void AnimationTick();
	void Draw();

	glm::vec3 GetPosition();
};
