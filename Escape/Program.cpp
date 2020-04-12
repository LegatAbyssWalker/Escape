#include "Program.h"

Program::Program(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath) {
	/*-------------------------------------------------------------------------------------------------------------------*/
	// Retrieve vertex and fragment code from filepath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	// Ensure ifstream objects can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// Open files
	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);

	std::stringstream vShaderStream, fShaderStream;

	// Read buffer contents into streams
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	// Close file handlers
	vShaderFile.close();
	fShaderFile.close();

	// Convert stream intro string
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();

	// If geometry shader path is present, load in a geometry shader
	if (!geometryPath.empty()) {
		gShaderFile.open(geometryPath);
		std::stringstream gShaderStream;
		gShaderStream << gShaderFile.rdbuf();
		gShaderFile.close();
		geometryCode = gShaderStream.str();
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	/*-------------------------------------------------------------------------------------------------------------------*/
	// Compile shaders
	GLuint vertex = 0, fragment = 0, geometry = 0;

	// Vertex
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// Fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	// Geometry
	if (!geometryPath.empty()) {
		const char* gShaderCode = geometryCode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		checkCompileErrors(geometry, "GEOMETRY");
	}

	// Shader program
	programID = glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	if (!geometryPath.empty()) { glAttachShader(programID, geometry); }

	glLinkProgram(programID);
	checkCompileErrors(programID, "PROGRAM");

	// Delete the shader as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (!geometryPath.empty()) { glDeleteShader(geometry); }
}

Program::~Program() {
	glDeleteProgram(programID);
}

void Program::useProgram() {
	glUseProgram(programID);
}

void Program::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Program::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Program::setFloat(const std::string& name, float value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Program::setVec2(const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Program::setVec2(const std::string& name, GLfloat x, GLfloat y) const {
	glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
}

void Program::setVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Program::setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const {
	glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}

void Program::setVec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Program::setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const {
	glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}

void Program::setMat2(const std::string& name, const glm::mat2& mat) const {
	glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Program::setMat3(const std::string& name, const glm::mat3& mat) const {
	glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Program::setMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Program::checkCompileErrors(GLuint shaderType, std::string type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shaderType, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderType, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << '\n' << infoLog << "\n -- --------------------------------------------------- -- \n";
		}
	}
	else {
		glGetProgramiv(shaderType, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderType, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_LINKING_ERROR of type: " << type << '\n' << infoLog << "\n -- --------------------------------------------------- -- \n";
		}
	}
}