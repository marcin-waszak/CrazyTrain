#pragma once

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Includes
#include <ctime>

// Other includes
#include "Input.h"
#include "Shader.h"
#include "LightsManager.h"
#include "Material.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Camera.h"
#include "CuboidModel.h"
#include "RailsAssemly.h"
#include "TrainAssembly.h"

class Core
{
	void DoMovement();

	// Deltatime
	GLfloat delta_time_ = 0.0f;  // Time between current frame and last frame
	GLfloat last_frame_ = 0.0f;  // Time of last frame
	Camera camera_;
	Input* input_;

public:
	Core();
	~Core();

	void Start();
};

