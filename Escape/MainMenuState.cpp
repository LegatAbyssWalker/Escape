#include "MainMenuState.h"

MainMenuState::MainMenuState(StateMachine& machine, GLWindow& window, bool replace) 
	: State(machine, window, replace), window(window), 
	// Text
	title(window), credit(window), start(window) {
	
	for (auto& font : font) { font.loadFont(ARIAL_FONT_LOCATION, 100); }

	// Text
	title.createText(glm::vec2( -0.15, 0.5), 120, &font[0], "ESCAPE");
	credit.createText(glm::vec2( 0.6,  0.8), 30,  &font[1], "CREATED BY: LEGATABYSSWALKER");
	start.createText(glm::vec2( -0.5, -0.5), 90,  &font[2], "Press Space Once to Start (Please Wait)");


	// Window 
	this->window.setMouseVisible(true);
}

void MainMenuState::keyboardInputs(sf::Keyboard::Key& key, bool isPressed) {
	if (key == sf::Keyboard::Escape) { machine.quit(); }
	if (key == sf::Keyboard::Space)  { machine.run(machine.buildState<PlayingState>(machine, window, true)); } 
}

void MainMenuState::updateEvents() {
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

void MainMenuState::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);


	title.render();
	credit.render();
	start.render();


	window.swapBuffers();
}
