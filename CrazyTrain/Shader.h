#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
        try
        {
			LoadVertexShader(vertexPath);
			LoadFragmentShader(fragmentPath);
        }
        catch (std::ifstream::failure e)
        {
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
		std::ifstream vShaderFile;
		std::stringstream vShaderStream;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		vShaderFile.open(path);

		vShaderStream << vShaderFile.rdbuf();
		vShaderFile.close();
		vertex_code_ = vShaderStream.str();
	}

	void LoadFragmentShader(const char* path) {
		std::ifstream fShaderFile;
		std::stringstream fShaderStream;

		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.open(path);

		fShaderStream << fShaderFile.rdbuf();
		fShaderFile.close();
		fragment_code_ = fShaderStream.str();
	}

	void CompileShaders() {
		const GLchar* vShaderCode = vertex_code_.c_str();
		const GLchar* fShaderCode = fragment_code_.c_str();
		GLuint vertex;
		GLuint fragment;

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		// Shader Program
		this->program_ = glCreateProgram();
		glAttachShader(this->program_, vertex);
		glAttachShader(this->program_, fragment);

		glLinkProgram(this->program_);
		checkCompileErrors(this->program_, "PROGRAM");
		// Delete the shaders as they're linked and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

    void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if(type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: "
					<< type << "|\n" << infoLog
					<< "\n| -- --------------------------|" << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if(!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: "
					<< type << "|\n" << infoLog
					<< "\n| -- ------------------------- |" << std::endl;
			}
		}
	}
};

#endif
