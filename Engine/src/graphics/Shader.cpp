#include "Shader.h"

namespace engine { namespace graphics {

	Shader::Shader(char* vertexShader, char* fragmentShader) {
		this->programID = glCreateProgram();
		this->vertexShaderID = compileShader(vertexShader, GL_VERTEX_SHADER);
		this->fragmentShaderID = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
		glAttachShader(this->programID, this->vertexShaderID);
		glAttachShader(this->programID, this->fragmentShaderID);
		glLinkProgram(this->programID);

		glDeleteShader(this->vertexShaderID);
		glDeleteShader(this->fragmentShaderID);
	}

	Shader::~Shader() {
		glDetachShader(this->programID, this->vertexShaderID);
		glDetachShader(this->programID, this->fragmentShaderID);
		glDeleteProgram(this->programID);
	}

	GLuint Shader::getUniformLocation(char* name) {
		if (uniforms.find(name) == uniforms.end())
			uniforms.emplace(name, glGetUniformLocation(programID, name));
		return uniforms[name];
	}

	void Shader::loadUniformMat4f(GLuint location, math::Matrix4f matrix) {
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix.elements);
	}

	void Shader::recompileShader(char* vertexShader, char* fragmentShader) {
		glDetachShader(this->programID, this->vertexShaderID);
		glDetachShader(this->programID, this->fragmentShaderID);

		this->vertexShaderID = compileShader(vertexShader, GL_VERTEX_SHADER);
		this->fragmentShaderID = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

		glAttachShader(this->programID, this->vertexShaderID);
		glAttachShader(this->programID, this->fragmentShaderID);
		glLinkProgram(programID);

		glDeleteShader(this->vertexShaderID);
		glDeleteShader(this->fragmentShaderID);
	}

	GLuint Shader::compileShader(char* source, GLenum type) {
		GLuint id = glCreateShader(type);

		glShaderSource(id, 1, &source, 0);
		glCompileShader(id);
		
		GLint success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (!success) {
			GLchar infoLog[512];
			glGetShaderInfoLog(id, 512, 0, infoLog);

			std::cout << "Error compiling " << ((type == GL_VERTEX_SHADER) ? "VERTEX_SHADER " : "FRAGMENT_SHADER ") << infoLog << std::endl;
			system("pause");
			glDeleteShader(id);
			return -1;
		}

		return id;
	}

	void Shader::enable() {
		glUseProgram(this->programID);
	}

	void Shader::disable() {
		glUseProgram(0);
	}
}}