#include "TrainAssembly.h"

TrainAssembly::TrainAssembly(Camera* camera, LightsManager* lights_manager, Shader* shader)
	: wheel_material_(shader, 32.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\container2.png",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\container2_specular.png"),
	rod_material_(shader, 32.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\ametal_m01.jpg",
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\specular.png"),
	platform_material_(shader, 32.f,
		"C:\\Users\\Marcin\\Documents\\Visual Studio 2015\\Projects\\CrazyTrain\\assets\\wood_m01_usat.jpg"),

	wheel1_(.5f, .5f, .1f, &wheel_material_, camera, lights_manager),
	wheel2_(.5f, .5f, .1f, &wheel_material_, camera, lights_manager),
	wheel3_(.5f, .5f, .1f, &wheel_material_, camera, lights_manager),
	wheel4_(.5f, .5f, .1f, &wheel_material_, camera, lights_manager),
	connecting_rod1_(glm::vec3(.05f, .05f, 3.05f), &rod_material_, camera, lights_manager),
	connecting_rod2_(glm::vec3(.05f, .05f, 3.05f), &rod_material_, camera, lights_manager),
	platform_(glm::vec3(1.9f, .2f, 5.f), &platform_material_, camera, lights_manager) {

	wheel1_.SetInitRotation(90.f, glm::vec3(0.f, 0.f, 1.0f));
	wheel1_.SetInitTranslation(glm::vec3(1.f, .6f, 1.5f));

	wheel2_.SetInitRotation(90.f, glm::vec3(0.f, 0.f, 1.0f));
	wheel2_.SetInitTranslation(glm::vec3(-1.f, .6f, 1.5f));

	wheel3_.SetInitRotation(90.f, glm::vec3(0.f, 0.f, 1.0f));
	wheel3_.SetInitTranslation(glm::vec3(1.0f, .6f, -1.5f));

	wheel4_.SetInitRotation(90.f, glm::vec3(0.f, 0.f, 1.0f));
	wheel4_.SetInitTranslation(glm::vec3(-1.0f, .6f, -1.5f));

	connecting_rod1_.SetInitTranslation(glm::vec3(1.025, 0.575f, 0.f));
	connecting_rod2_.SetInitTranslation(glm::vec3(-1.125, 0.575f, 0.f));

	platform_.SetInitTranslation(glm::vec3(-.05f, 0.6f - 0.2/2, 0.f));
}

TrainAssembly::~TrainAssembly() {
}

glm::vec3 TrainAssembly::GetPosition() {
	return translation_;
}

void TrainAssembly::AnimationTick() {
	GLfloat angle = 2500.f * sin(glfwGetTime() / 4.f);
	translation_ = glm::vec3(0.f, 0.f, glm::radians(angle));

	wheel1_.SetRotation(angle, glm::vec3(1.f, 0.f, 0.f));
	wheel2_.SetRotation(angle, glm::vec3(1.f, 0.f, 0.f));
	wheel3_.SetRotation(angle, glm::vec3(1.f, 0.f, 0.f));
	wheel4_.SetRotation(angle, glm::vec3(1.f, 0.f, 0.f));

	wheel1_.SetTranslation(translation_);
	wheel2_.SetTranslation(translation_);
	wheel3_.SetTranslation(translation_);
	wheel4_.SetTranslation(translation_);

	connecting_rod1_.SetTranslation(glm::vec3(0.f, 0.475 * cos(glm::radians(angle)), 0.475 * sin(glm::radians(angle))) + translation_);
	connecting_rod2_.SetTranslation(glm::vec3(0.f, 0.475 * cos(glm::radians(angle)), 0.475 * sin(glm::radians(angle))) + translation_);

	platform_.SetTranslation(translation_);

	wheel1_.UpdateModelMatrix();
	wheel2_.UpdateModelMatrix();
	wheel3_.UpdateModelMatrix();
	wheel4_.UpdateModelMatrix();

	connecting_rod1_.UpdateModelMatrix();
	connecting_rod2_.UpdateModelMatrix();

	platform_.UpdateModelMatrix();
}

void TrainAssembly::Draw() {
	AnimationTick();

	wheel1_.Draw();
	wheel2_.Draw();
	wheel3_.Draw();
	wheel4_.Draw();

	connecting_rod1_.Draw();
	connecting_rod2_.Draw();

	platform_.Draw();
}
