#pragma once

#include "Material.h"
#include "CuboidModel.h"
#include "ConeModel.h"

class RailsAssemly
{
	static const int WOODS = 64;

	Shader shader_cube_;
	Material box_material_;

	CuboidModel rail1_;
	CuboidModel rail2_;

	CuboidModel* woods_[WOODS];

public:
	RailsAssemly(Camera* camera, LightsManager* lights_manager);
	~RailsAssemly();

	void Draw();
};
