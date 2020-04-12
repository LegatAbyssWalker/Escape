#pragma once

#include "Object.h"
#include "State.h"
#include "Model.h"
#include "Player.h"
#include "Random.h"

#include "glm/glm.hpp"

#include <iostream>
#include <memory>
#include <cmath>

class Friends : public Object {
	public:
		Friends(GLWindow& window, std::string const& filePath);

		void update(GLfloat deltaTime, glm::vec3 playerPosition, glm::vec3 playerUp);
		void render(const glm::mat4 viewMatrix, const glm::mat4& projection);
		
		void calculateMovement();
		void moveFriend();

		bool isFriendDead();
		void setDead();

		float getVectorLength() { return glm::length(directionalVector); }
	
		template <typename T>
		GLfloat getBoundaryIndex(T min, T max) { return random.getNumberInRange(min, max); }

	private:
		Random<> random;

		bool isDead = false;

		glm::vec3 directionalVector;

		Model model;
		GLfloat deltaTime;

		glm::vec3 closeValue = glm::vec3(0.5, 0, 0.5);
		glm::vec3 playerXYZ;
		glm::vec3 playerUp;
};

