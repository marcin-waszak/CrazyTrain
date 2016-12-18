#include "Material.h"

Material::Material(Shader* shader, GLfloat shiness,
	const char* p_diffuse, const char* p_specular, const char* p_normal) {
	int width;
	int height;
	unsigned char* image;

	shader_ = shader;

	if (p_diffuse != nullptr) {
		glGenTextures(1, &diffuse_map_);

		image = SOIL_load_image(p_diffuse, &width, &height, 0, SOIL_LOAD_RGB);
		glBindTexture(GL_TEXTURE_2D, diffuse_map_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	}

	if (p_specular != nullptr) {
		glGenTextures(1, &specular_map_);

		image = SOIL_load_image(p_specular, &width, &height, 0, SOIL_LOAD_RGB);
		glBindTexture(GL_TEXTURE_2D, specular_map_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	}

	// bump mapping waits to implement
	glBindTexture(GL_TEXTURE_2D, 0);

	shader_->Use();
	glUniform1i(glGetUniformLocation(shader_->GetProgram(), "material_diffuse"), 0);
	glUniform1i(glGetUniformLocation(shader_->GetProgram(), "material_specular"), 1);
	glUniform1f(glGetUniformLocation(shader_->GetProgram(), "material_shininess"), shiness);
}

Material::~Material() {
	// need to cleanup
}

void Material::Use() const {
	shader_->Use();

	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse_map_);
	// Bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specular_map_);
}

Shader* Material::GetShader() const {
	return shader_;
}
