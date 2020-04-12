#pragma once

#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <array>

class Program {
	public:
		GLuint programID;

		Program() = default;
		Program(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
		~Program();

		void useProgram();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

		void setVec2(const std::string& name, const glm::vec2& value) const;
		void setVec2(const std::string& name, GLfloat x, GLfloat y) const;

		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const;

		void setVec4(const std::string& name, const glm::vec4& value) const;
		void setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;

		void setMat2(const std::string& name, const glm::mat2& mat) const;
		void setMat3(const std::string& name, const glm::mat3& mat) const;
		void setMat4(const std::string& name, const glm::mat4& mat) const;

	private:
		void checkCompileErrors(GLuint shaderType, std::string type);
};
