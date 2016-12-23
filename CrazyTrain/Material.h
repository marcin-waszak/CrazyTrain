#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include "Shader.h"

class Material {
public:
	Material(
		Shader* shader,
		GLfloat shiness = 0,
		const char* p_diffuse = nullptr,
		const char* p_specular = nullptr,
		const char* p_normal = nullptr);

	~Material();
	void Use() const;
	Shader* GetShader() const;

private:
	Shader* shader_;
	GLfloat shiness_;
	GLuint diffuse_map_;
	GLuint specular_map_;
	GLuint normal_map_;
};
