#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <memory>
#include <vector>
#include <array>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "FileLocations.h"
#include "Variables.h"
#include "GLWindow.h"
#include "Random.h"

#include "Player.h"
#include "Entity.h"

class StreetManager {
	public:
		StreetManager(GLWindow& window, glm::vec3 streetScaleValue);

		void render(const glm::mat4 viewMatrix, const glm::mat4& projection);

		glm::vec3 getLow() const { 
			glm::vec3 low;
			low.x = street->getModelPosition().x - street->getSize().x;
			low.y = street->getModelPosition().y - street->getSize().y;
			low.z = street->getModelPosition().z - street->getSize().z;

			return low;
		}

		glm::vec3 getHigh() const {
			glm::vec3 high;
			high.x = street->getModelPosition().x + street->getSize().x;
			high.y = street->getModelPosition().y + street->getSize().y;
			high.z = street->getModelPosition().z + street->getSize().z;

			return high;
		}

		std::unique_ptr<Entity>& getStreet() { return street; }

	private:
		GLWindow& window;

		bool removed;

		std::array<Random<>, 2> random;
		std::array<Random<>, 2> randomCarAmount;
		std::array<Random<>, 2> randomCarPosition;

		std::unique_ptr<Entity> street;
		std::unique_ptr<Entity> house;
		std::unique_ptr<Entity> finishline;
		std::vector<std::unique_ptr<Entity>> streetlampVector;
		std::vector<std::unique_ptr<Entity>> benchVector;
		std::vector<std::unique_ptr<Entity>> carVector;
};

