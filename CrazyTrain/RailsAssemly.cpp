#include "RailsAssemly.h"

RailsAssemly::RailsAssemly(Camera* camera, LightsManager* lights_manager)
	: shader_cube_(
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\basic_lighting.vs",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\basic_lighting.frag"),
	box_material_(&shader_cube_, 32.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\container2.png",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\container2_specular.png"),
	rail1_(glm::vec3(.1f, .1f, 91.f), &box_material_, camera, lights_manager),
	rail2_(glm::vec3(.1f, .1f, 91.f), &box_material_, camera, lights_manager) {
	rail1_.SetInitTranslation(glm::vec3(0.95f, 0.f, 0.f));
	rail2_.SetInitTranslation(glm::vec3(-1.05f, 0.f, 0.f));

	for (int i = 0; i < WOODS; ++i) {
		woods_[i] = new CuboidModel(glm::vec3(2.3f, .05f, .3f), &box_material_, camera, lights_manager);
		woods_[i]->SetInitTranslation(glm::vec3(-0.05f, 0.f, -89.f / 2 + i * 91.f / WOODS));
	}
}

RailsAssemly::~RailsAssemly() {
	for (int i = 0; i < WOODS; ++i)
		delete woods_[i];
}

void RailsAssemly::Draw() {
	rail1_.Draw();
	rail2_.Draw();

	for (int i = 0; i < WOODS; ++i)
		woods_[i]->Draw();
}
