#include "EndMenuState.h"

EndMenuState::EndMenuState(StateMachine& machine, GLWindow& window, bool replace)
	: State(machine, window, replace), window(window),
	// Text
	end(window), thank(window), credits(window) {

	for (auto& font : font) { font.loadFont(ARIAL_FONT_LOCATION, 100); }

	// Text
	end.createText(    glm::vec2(-0.15, 0.5), 120, &font[0], "THE END!");
	credits.createText(glm::vec2(-0.2, -0.5), 90,  &font[2], "THANKS FOR PLAYING");
	thank.createText(  glm::vec2( 0.6,  0.8), 30,  &font[1], "CREATED BY: LEGATABYSSWALKER");


	// Window 
	this->window.setMouseVisible(true);
}

void EndMenuState::keyboardInputs(sf::Keyboard::Key& key, bool isPressed) {
	if (key == sf::Keyboard::Escape) { machine.quit(); }
}

void EndMenuState::updateEvents() {
	while (window.getWindow().pollEvent(sfEvent)) {
		auto keyCode = sfEvent.key.code;
		switch (sfEvent.type) {
			case sf::Event::Resized:
				this->window.setViewPort(glm::vec2(0), glm::vec2(sfEvent.size.width, sfEvent.size.height));
				break;

			case sf::Event::Closed:
				machine.quit();
				break;

			case sf::Event::KeyPressed:
				keyboardInputs(keyCode, true);
				break;

			case sf::Event::KeyReleased:
				keyboardInputs(keyCode, false);
				break;
		}
	}
}

void EndMenuState::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);


	end.render();
	thank.render();
	credits.render();


	window.swapBuffers();
}
