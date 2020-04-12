#pragma once

#include "Object.h"
#include "State.h"
#include "Model.h"
#include "Player.h"
#include "Random.h"
#include "StreetManager.h"

#include "glm/glm.hpp"

#include <iostream>
#include <memory>
#include <cmath>
#include <vector>
#include <array>

class Officers : public Object {
	public:
		Officers(GLWindow& window, std::string const& filePath, std::unique_ptr<StreetManager>& manager);

		void update(GLfloat deltaTime, std::unique_ptr<Player>& player, bool useCameraPosition = true);
		void render(const glm::mat4 viewMatrix, const glm::mat4& projection);

		void updateRotation();

		void calculateMovement();
		void moveOfficer(GLfloat generalSpeed = 0.5);

		float getVectorLength() { return glm::length(directionalVector); }

		template <typename T>
		GLfloat getBoundaryIndex(T min, T max) { return random[0].getFloat(min, max); }

		bool isColliding(std::unique_ptr<Player>& player, bool useCameraPosition);

	private:
		int officerSign;
		std::array<Random<>, 2> random;

		glm::vec3 directionalVector;

		Model model;
		GLfloat deltaTime;

		glm::vec3 closeValue = glm::vec3(0.5, 0, 0.5);
		glm::vec3 playerXYZ;
		glm::vec3 playerUp;
};