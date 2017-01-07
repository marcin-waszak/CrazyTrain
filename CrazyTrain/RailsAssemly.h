#pragma once

#include "Material.h"
#include "CuboidModel.h"
#include "ConeModel.h"

class RailsAssemly
{
	static const int WOODS = 64;

	Material rail_material_;
	Material wood_material_;

	CuboidModel rail1_;
	CuboidModel rail2_;

	CuboidModel* woods_[WOODS];

public:
	RailsAssemly(Camera* camera, LightsManager* lights_manager, Shader* shader);
	~RailsAssemly();

	void Draw();
};
