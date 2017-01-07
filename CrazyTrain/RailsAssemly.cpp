#include "RailsAssemly.h"

RailsAssemly::RailsAssemly(Camera* camera, LightsManager* lights_manager, Shader* shader)
	: rail_material_(shader, 32.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\ametal_m01.jpg",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\specular.png"),
	wood_material_(shader, 32.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\wood_m10.jpg"),
	rail1_(glm::vec3(.1f, .1f, 91.f), &rail_material_, camera, lights_manager),
	rail2_(glm::vec3(.1f, .1f, 91.f), &rail_material_, camera, lights_manager) {
	rail1_.SetInitTranslation(glm::vec3(0.95f, 0.f, 0.f));
	rail2_.SetInitTranslation(glm::vec3(-1.05f, 0.f, 0.f));

	for (int i = 0; i < WOODS; ++i) {
		woods_[i] = new CuboidModel(glm::vec3(2.3f, .05f, .3f), &wood_material_, camera, lights_manager);
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
