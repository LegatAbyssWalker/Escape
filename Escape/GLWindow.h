#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "FileLocations.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class GLWindow {
	public:
		GLWindow() = default;
		~GLWindow();

		void initWindow();
		void swapBuffers();
	
		void setMouseVisible(bool visible);
		
		bool isOpen() { return window.isOpen(); }
		sf::Window& getWindow() { return window; }


		glm::mat4 getPerspectiveMatrix() {
			return glm::perspective(glm::radians(45.f), 
				(GLfloat)getWindow().getSize().x / getWindow().getSize().y, 0.1f, 100.f);
		}

		glm::mat4 getOrthographicMatrix() {
			return glm::ortho(0.f, (float)window.getSize().x, (float)window.getSize().y, 0.f, -1.0f, 1.0f);
		}

	private:
		sf::Window window;
};

