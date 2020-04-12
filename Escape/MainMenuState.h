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

#include "PlayingState.h"
#include "Font.h"
#include "Text.h"

#include "Camera.h"

class MainMenuState : public State {
	public:
		MainMenuState(StateMachine& machine, GLWindow& window, bool replace = true);

		void keyboardInputs(sf::Keyboard::Key& key, bool isPressed);

		void updateEvents();
		void update() {}
		void render();


	private:
		GLWindow& window;
		sf::Event sfEvent;

		std::array<Font, 3> font;
		Text title, credit, start;
};

