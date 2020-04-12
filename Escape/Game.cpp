#include "Game.h"

void Game::run() {
	window = std::make_unique<GLWindow>();
	window->initWindow();

	machine.run(StateMachine::buildState<MainMenuState>(machine, *window, true));

	while (window->isOpen() && machine.running()) {
		machine.nextState();
		machine.updateEvents();
		machine.update();
		machine.render();
	}
}
