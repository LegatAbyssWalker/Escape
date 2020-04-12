#pragma once

#include "State.h"
#include "Camera.h"
#include "GLWindow.h"
#include "Variables.h"
#include "Program.h"
#include "Mesh.h"
#include "FileLocations.h"
#include "Object.h"
#include "Entity.h"

#include <iostream>
#include <memory>

enum class Wheel {
	WHEEL_UP,
	WHEEL_DOWN,
	WHEEL_STATIC
};

class Player {
	public:
		Player(GLWindow& window, glm::vec3 cameraPosition, glm::mat4 projection);

		void mouseUpdate(Wheel wheel);
		void keyboardUpdate(Movement movement, GLfloat deltaTime);

		void update();
		void render(const glm::mat4 viewMatrix, const glm::mat4& projection);

		Camera& getCamera() { return camera; }
		std::unique_ptr<Entity>& getBush() { return bush; }

		bool boundsZ(std::unique_ptr<Entity>& street);

	private:
		glm::f32 rotationAmount = 0;
		float time = 0;
		
		bool isCrouching = false;

		std::unique_ptr<Entity> bush;

		Movement movement;
		GLWindow& window;

		Camera camera;
		GLfloat lastX = window.getWindow().getSize().x / 2.f;
		GLfloat lastY = window.getWindow().getSize().y / 2.f;
		bool firstMouse = true;
};