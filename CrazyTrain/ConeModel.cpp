#include "ConeModel.h"

ConeModel::ConeModel(
	GLfloat radius_a,
	GLfloat radius_b,
	GLfloat height,
	Material* material,
	Camera* camera,
	LightsManager* lights_manager) {
	material_ = material;
	shader_ = material_->GetShader();
	camera_ = camera;
	lights_manager_ = lights_manager;

	GLfloat theta = 2 * glm::pi<GLfloat>() / CONE_SEGMENTS;

	for (int i = 0; i < CONE_SEGMENTS; ++i) {
		glm::vec3 v_base(
			0.0f,
			0.0f,
			0.0f
		);
		glm::vec3 v_radius1(
			sin(i * theta),
			0.0f,
			cos(i * theta)
		);
		glm::vec3 v_radius2(
			sin((i + 1) * theta),
			0.0f,
			cos((i + 1) * theta)
		);

		glm::vec3 v_baseA = v_base;
		glm::vec3 v_radiusA1 = v_radius1 * radius_a;
		glm::vec3 v_radiusA2 = v_radius2 * radius_a;

		glm::vec3 height_vec(
			0.0f,
			height,
			0.0f
		);

		glm::vec3 v_baseB = v_baseA + height_vec;
		glm::vec3 v_radiusB1 = v_radius1 * radius_b + height_vec;
		glm::vec3 v_radiusB2 = v_radius2 * radius_b + height_vec;

		// bottom
		vertices_[36 * i + 0] = v_baseA.x;
		vertices_[36 * i + 1] = v_baseA.y;
		vertices_[36 * i + 2] = v_baseA.z;

		vertices_[36 * i + 3] = v_radiusA1.x;
		vertices_[36 * i + 4] = v_radiusA1.y;
		vertices_[36 * i + 5] = v_radiusA1.z;

		vertices_[36 * i + 6] = v_radiusA2.x;
		vertices_[36 * i + 7] = v_radiusA2.y;
		vertices_[36 * i + 8] = v_radiusA2.z;

		//top
		vertices_[36 * i + 9] = v_radiusB2.x;
		vertices_[36 * i + 10] = v_radiusB2.y;
		vertices_[36 * i + 11] = v_radiusB2.z;

		vertices_[36 * i + 12] = v_radiusB1.x;
		vertices_[36 * i + 13] = v_radiusB1.y;
		vertices_[36 * i + 14] = v_radiusB1.z;

		vertices_[36 * i + 15] = v_baseB.x;
		vertices_[36 * i + 16] = v_baseB.y;
		vertices_[36 * i + 17] = v_baseB.z;

		//|_ side triangle
		vertices_[36 * i + 18] = v_radiusA1.x;
		vertices_[36 * i + 19] = v_radiusA1.y;
		vertices_[36 * i + 20] = v_radiusA1.z;

		vertices_[36 * i + 21] = v_radiusB1.x;
		vertices_[36 * i + 22] = v_radiusB1.y;
		vertices_[36 * i + 23] = v_radiusB1.z;

		vertices_[36 * i + 24] = v_radiusA2.x;
		vertices_[36 * i + 25] = v_radiusA2.y;
		vertices_[36 * i + 26] = v_radiusA2.z;

		// ^| side triagle
		vertices_[36 * i + 27] = v_radiusA2.x;
		vertices_[36 * i + 28] = v_radiusA2.y;
		vertices_[36 * i + 29] = v_radiusA2.z;

		vertices_[36 * i + 30] = v_radiusB2.x;
		vertices_[36 * i + 31] = v_radiusB2.y;
		vertices_[36 * i + 32] = v_radiusB2.z;

		vertices_[36 * i + 33] = v_radiusB1.x;
		vertices_[36 * i + 34] = v_radiusB1.y;
		vertices_[36 * i + 35] = v_radiusB1.z;
	}

	for (int i = 0; i < 2 * 2 * CONE_SEGMENTS; ++i) {
		if (i % 4 < 2) {
			glm::vec3 vertex1(vertices_[9 * i + 0], vertices_[9 * i + 1], vertices_[9 * i + 2]);
			glm::vec3 vertex2(vertices_[9 * i + 3], vertices_[9 * i + 4], vertices_[9 * i + 5]);
			glm::vec3 vertex3(vertices_[9 * i + 6], vertices_[9 * i + 7], vertices_[9 * i + 8]);

			glm::vec3 vector1 = vertex2 - vertex1;
			glm::vec3 vector2 = vertex3 - vertex1;

			glm::vec3 normal = -glm::cross(vector1, vector2);

			normals_[9 * i + 0] = normals_[9 * i + 3] = normals_[9 * i + 6] = normal.x;
			normals_[9 * i + 1] = normals_[9 * i + 4] = normals_[9 * i + 7] = normal.y;
			normals_[9 * i + 2] = normals_[9 * i + 5] = normals_[9 * i + 8] = normal.z;
		}
	}

	for (int i = 0; i < 12 * CONE_SEGMENTS; ++i) {
		if (i % 12 < 6)
			continue;

		glm::vec3 vertex(
			vertices_[3 * i + 0],
			0.0f,
			vertices_[3 * i + 2]
		);

		vertex = glm::normalize(vertex);

		normals_[3 * i + 0] = vertex.x;
		normals_[3 * i + 1] = vertex.y;
		normals_[3 * i + 2] = vertex.z;
	}

	GLfloat texture[2 * 2 * 3 * 3 * CONE_SEGMENTS];

	for (int i = 0; i < 2 * 3 * CONE_SEGMENTS; ++i) {
		texture[6 * i + 0] = 0.0f;
		texture[6 * i + 1] = 0.0f;

		texture[6 * i + 2] = 1.0f;
		texture[6 * i + 3] = 0.0f;

		texture[6 * i + 4] = 1.0f;
		texture[6 * i + 5] = 1.0f;
	}

	GetUniformLocations();

	////

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_vertices_);
	glGenBuffers(1, &vbo_normals_);

	glBindVertexArray(vao_);

	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices_);
	glBufferData(GL_ARRAY_BUFFER, 2 * 2 * 3 * 3 * CONE_SEGMENTS * sizeof(GLfloat), vertices_, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals_);
	glBufferData(GL_ARRAY_BUFFER, 2 * 2 * 3 * 3 * CONE_SEGMENTS * sizeof(GLfloat), normals_, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	// Texture
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texture_);
	glBufferData(GL_ARRAY_BUFFER, 2 * 2 * 3 * 3 * CONE_SEGMENTS * sizeof(GLfloat), texture, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ConeModel::~ConeModel() {
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_vertices_);
	glDeleteBuffers(1, &vbo_normals_);
	glDeleteBuffers(1, &vbo_texture_);
}

void ConeModel::Draw() {
	glm::mat4 view_matrix = camera_->GetViewMatrix();
	glm::mat4 projection_matrix = camera_->GetProjectionMatrix();
	glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_));

	material_->Use();

	glUniform3fv(view_position_location_, 1, glm::value_ptr(camera_->position_));

	// Create camera transformations
	glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(model_));
	glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	glUniformMatrix3fv(normal_matrix_location_, 1, GL_FALSE, glm::value_ptr(normal_matrix));

	auto plights = lights_manager_->GetPointLights();
	auto slights = lights_manager_->GetSpotLights();

	// Set pointlights properties
	for (size_t i = 0; i < plights.size(); ++i) {
		glUniform3fv(plight_color_location_[i], 1, glm::value_ptr(plights[i].color));
		glUniform3fv(plight_position_location_[i], 1, glm::value_ptr(plights[i].position));
		glUniform1f(plight_constant_location_[i], 1.f);
		glUniform1f(plight_linear_location_[i], 0.f);
		glUniform1f(plight_quadratic_location_[i], plights[i].attenuation);
		glUniform1f(plight_ambient_location_[i], 0.03f);
		glUniform1f(plight_diffuse_location_[i], plights[i].diffuse);
		glUniform1f(plight_specular_location_[i], plights[i].specular);
	}

	// Set spotlights properties
	for (size_t i = 0; i < slights.size(); ++i) {
		glUniform3fv(slight_color_location_[i], 1, glm::value_ptr(slights[i].color));
		glUniform3fv(slight_position_location_[i], 1, glm::value_ptr(slights[i].position));
		glUniform3fv(slight_direction_location_[i], 1, glm::value_ptr(slights[i].direction));
		glUniform1f(slight_constant_location_[i], 1.f);
		glUniform1f(slight_linear_location_[i], 0.f);
		glUniform1f(slight_quadratic_location_[i], slights[i].attenuation);
		glUniform1f(slight_ambient_location_[i], 0.03f);
		glUniform1f(slight_diffuse_location_[i], slights[i].diffuse);
		glUniform1f(slight_specular_location_[i], slights[i].specular);
		glUniform1f(slight_cutoff_location_[i], slights[i].cutoff);
		glUniform1f(slight_outer_cutoff_location_[i], slights[i].outer_cutoff);
	}

	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 2 * 2 * 3 * CONE_SEGMENTS);
	glBindVertexArray(0);
}

void ConeModel::GetUniformLocations() {
	Model::GetUniformLocations();

	char buffer[64];
	GLint location;

	for (size_t i = 0; i < lights_manager_->GetPointLights().size(); ++i) {
		snprintf(buffer, sizeof(buffer), "pointLights[%zu].color", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_color_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].position", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_position_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].constant", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_constant_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].linear", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_linear_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].quadratic", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_quadratic_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].ambient", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_ambient_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].diffuse", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_diffuse_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "pointLights[%zu].specular", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		plight_specular_location_.push_back(location);
	}

	for (size_t i = 0; i < lights_manager_->GetSpotLights().size(); ++i) {
		snprintf(buffer, sizeof(buffer), "spotLights[%zu].color", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_color_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].position", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_position_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].direction", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_direction_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].constant", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_constant_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].linear", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_linear_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].quadratic", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_quadratic_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].ambient", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_ambient_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].diffuse", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_diffuse_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].specular", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_specular_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].cutoff", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_cutoff_location_.push_back(location);

		snprintf(buffer, sizeof(buffer), "spotLights[%zu].outer_cutoff", i);
		location = glGetUniformLocation(shader_->GetProgram(), buffer);
		slight_outer_cutoff_location_.push_back(location);
	}
}
