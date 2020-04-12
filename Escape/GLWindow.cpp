#include "GLWindow.h"

#include "Variables.h"


GLWindow::~GLWindow() {
	window.close();
}

void GLWindow::initWindow() {
	std::string title;
	sf::VideoMode windowBounds;
	sf::ContextSettings contextSettings;
	unsigned int framerateLimit = 120;

	std::ifstream in(WINDOW_INI_CONFIG);
	if (in.is_open()) {
		std::getline(in, title);
		in >> windowBounds.width >> windowBounds.height;
		in >> framerateLimit;
		in >> contextSettings.majorVersion >> contextSettings.minorVersion;
		in >> contextSettings.depthBits;
	}
	in.close();

	// SFML
	window.create(windowBounds, title, sf::Style::Default, contextSettings);
	window.setPosition({window.getPosition().x, window.getPosition().y - 50});
	window.setFramerateLimit(framerateLimit);
	window.setActive();

    if(glewInit() != GLEW_OK) {
        std::cout << "Glew doesn't open correnctly";
    }

	glEnable(GL_DEPTH_TEST);
	
	// Viewport
	setViewPort(glm::vec2(0), glm::vec2(getWindow().getSize().x, getWindow().getSize().y));
}

void GLWindow::swapBuffers() {
	window.display();
}

void GLWindow::setMouseVisible(bool visible) {
	window.setMouseCursorVisible(visible);
}

void GLWindow::setViewPort(glm::vec2 origin, glm::vec2 newWidthNewHeight) {
	glViewport(origin.x, origin.y, newWidthNewHeight.x, newWidthNewHeight.y); // Lower left corner should be (0, 0);
}
