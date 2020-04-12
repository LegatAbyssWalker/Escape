#include "PlayingState.h"

PlayingState::PlayingState(StateMachine& machine, GLWindow& window, bool replace)
	: State(machine, window, replace), window(window) {

	// StreetManager
	manager = std::make_unique<StreetManager>(window, glm::vec3(20, 0, 2));

	// Player
	player = std::make_unique<Player>(window, glm::vec3(0, 0.5, 0), window.getPerspectiveMatrix());

	// Officers
	std::string officerType[2] = {
		OFFICER_ONE_MODEL_LOCATION,
		OFFICER_TWO_MODEL_LOCATION
	};

	int officerAmount = random[3].getInt(4, 12);
	for (int i = 0; i < officerAmount; i++) {
		int randomType = random[0].getInt(0, 1);
		officerVector.emplace_back(new Officers(window, officerType[randomType], manager));
		glm::vec3 position;
		position.x = random[1].getInt(  manager->getLow().x + 4, manager->getHigh().x - 2);
		position.z = random[2].getFloat(manager->getLow().z + 1, manager->getHigh().z - 1);
		position.y = 0.1;

		officerVector[i]->setModelPosition(position);
		officerVector[i]->setScale(SCALE_VALUE);
	}

	// Window 
	this->window.setMouseVisible(false);
}

void PlayingState::keyboardInputs(sf::Keyboard::Key& key, bool isPressed) {
	if (key == sf::Keyboard::Escape) { machine.quit(); }
}
void PlayingState::updateEvents() {
	while (window.getWindow().pollEvent(sfEvent)) {
		auto keyCode = sfEvent.key.code;
		auto wheelCode = sfEvent.mouseWheelScroll.delta;
		switch (sfEvent.type) { 
			case sf::Event::Closed:
				machine.quit();
				break;  

			case sf::Event::KeyPressed:
				keyboardInputs(keyCode, true);
				break;

			case sf::Event::KeyReleased:
				keyboardInputs(keyCode, false);
				break;

			case sf::Event::EventType::MouseWheelScrolled:
				if (wheelCode > 0)  { player->mouseUpdate(Wheel::WHEEL_UP); }
				if (wheelCode < 0)  { player->mouseUpdate(Wheel::WHEEL_DOWN); }
				if (wheelCode == 0) { player->mouseUpdate(Wheel::WHEEL_STATIC); }

		}


		// Keyboard
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { player->keyboardUpdate(Movement::FORWARD,  deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { player->keyboardUpdate(Movement::LEFT,     deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { player->keyboardUpdate(Movement::BACKWARD, deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { player->keyboardUpdate(Movement::RIGHT,    deltaTime); }
	}
}

void PlayingState::update() {
	GLfloat now = clock.getElapsedTime().asSeconds();
	deltaTime = now - lastFrame;
	lastFrame = now;
	
	// Player
	player->update();
	if (player->getCamera().getPosition().x >= manager->getHigh().x) { machine.run(machine.buildState<EndMenuState>(machine, window, true)); }


	// Officer
	for (auto& officers : officerVector) {
		officers->update(deltaTime, player, true);
		officers->updateRotation();
		officers->calculateMovement();

		// Checks vector length
		if (officers->getVectorLength() < officers->getBoundaryIndex(0.5, 1.5)) { officers->moveOfficer(0.5); }

		// Checks if player moves out of the street 
		if (player->boundsZ(manager->getStreet())) { officers->moveOfficer(0.5); }

		// Collision detection test
		if (officers->isColliding(player, true)) { machine.quit(); }
	}

}

void PlayingState::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 1.f, 1.f, 1.f);


	player->render(player->getCamera().calculateViewMatrix(), window.getPerspectiveMatrix());
	manager->render(player->getCamera().calculateViewMatrix(), window.getPerspectiveMatrix());

	for (auto& officers : officerVector) { officers->render(player->getCamera().calculateViewMatrix(), window.getPerspectiveMatrix()); }


	window.swapBuffers();
}
