#pragma once

#include "Mesh.h"
#include "Program.h"
#include "Variables.h"
#include "State.h"
#include "Model.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

struct Object {
	public:
		Object() = default;
		Object(GLWindow& window) : window(window) { program = std::make_unique<Program>(BASIC_VERTEX_SHADER, BASIC_FRAGMENT_SHADER); }

		void setModelPosition(glm::vec3 position) { this->position = position; }
		void setScale(glm::vec3 scaleValue) { this->scaleValue = scaleValue; }

		void setRotation(glm::f32 rotationAngle, glm::vec3 rotationAxis) { 
			this->rotationAngle = rotationAngle;  
			this->rotationAxis = rotationAxis;
		}

		void move(glm::vec3 offset) { setModelPosition(glm::vec3(getModelPosition().x + offset.x, getModelPosition().y + offset.y, getModelPosition().z + offset.z)); }

		glm::vec3 getModelPosition() const { return position; }
		glm::vec3 getSize() const { return scaleValue; }

		glm::f32 getRotationAngle() const { return rotationAngle; }
		glm::vec3 getRotationAxis() const { return rotationAxis; }

	protected:
		GLWindow& window;
		std::unique_ptr<Program> program = nullptr;

		glm::f32 rotationAngle = 0;
		glm::vec3 rotationAxis = glm::vec3(0, 1, 0);

		glm::vec3 position = glm::vec3(0);
		glm::vec3 scaleValue = SCALE_VALUE;
};
