#pragma once

#include "State.h"
#include "StateMachine.h"
class StateMachine;

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

#include "StreetManager.h"

#include "Player.h"
#include "Officers.h"

#include "EndMenuState.h"

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, GLWindow& window, bool replace = true);

		void keyboardInputs(sf::Keyboard::Key& key, bool isPressed);

		void updateEvents();
		void update();
		void render();

	private:
		glm::f32 officerRotation = 0;

		GLWindow& window;
		sf::Event sfEvent;
		sf::Clock clock;
		GLfloat deltaTime = 0, lastFrame = 0;

		bool managerChecked = false;

		std::array<Random<>, 6> random;
		std::unique_ptr<Player> player = nullptr;
		std::unique_ptr<StreetManager> manager;
		std::vector<std::unique_ptr<Officers>> officerVector;
};
