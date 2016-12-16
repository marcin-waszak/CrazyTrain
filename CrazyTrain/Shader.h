#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	Shader(const GLchar* vertex_path, const GLchar* fragment_path) {
		try {
			LoadVertexShader(vertex_path);
			LoadFragmentShader(fragment_path);
		} catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		CompileShaders();
	}

	// Uses the current shader
	void Use() const {
		glUseProgram(this->program_);
	}

	GLuint GetProgram() const {
		return program_;
	}

private:
	std::string vertex_code_;
	std::string fragment_code_;

	GLuint program_;

	void LoadVertexShader(const char* path) {
		std::ifstream vertex_shader_file;
		std::stringstream vertex_shader_stream;

		vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		vertex_shader_file.open(path);

		vertex_shader_stream << vertex_shader_file.rdbuf();
		vertex_shader_file.close();
		vertex_code_ = vertex_shader_stream.str();
	}

	void LoadFragmentShader(const char* path) {
		std::ifstream fragment_shader_file;
		std::stringstream fShaderStream;

		fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragment_shader_file.open(path);

		fShaderStream << fragment_shader_file.rdbuf();
		fragment_shader_file.close();
		fragment_code_ = fShaderStream.str();
	}

	void CompileShaders() {
		const GLchar* vertex_shader_code = vertex_code_.c_str();
		const GLchar* fragment_shader_code = fragment_code_.c_str();
		GLuint vertex;
		GLuint fragment;

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertex_shader_code, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragment_shader_code, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");

		// Shader Program
		this->program_ = glCreateProgram();
		glAttachShader(this->program_, vertex);
		glAttachShader(this->program_, fragment);

		glLinkProgram(this->program_);
		CheckCompileErrors(this->program_, "PROGRAM");
		// Delete the shaders as they're linked and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void CheckCompileErrors(GLuint shader, std::string type) {
		GLint success;
		GLchar info_log[1024];
		if(type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if(!success) {
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
				std::cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: "
					<< type << "|\n" << info_log
					<< "\n| -- --------------------------|" << std::endl;
			}
		} else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if(!success) {
				glGetProgramInfoLog(shader, 1024, NULL, info_log);
				std::cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: "
					<< type << "|\n" << info_log
					<< "\n| -- ------------------------- |" << std::endl;
			}
		}
	}
};
