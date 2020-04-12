#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "GLWindow.h"

#include <iostream>

enum Movement {
	FORWARD,
	LEFT,
	BACKWARD,
	RIGHT,
};


class Camera {
	public:
		Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), 
			GLfloat yaw = -90.f, GLfloat pitch = 0.f, GLfloat movementSpeed = 2.5f, GLfloat mouseSensitivity = 0.3f);

		void processKeyboard(Movement direction, GLfloat deltaTime);
		void processMouseMovement(GLWindow& window);

		const glm::vec3 getPosition() { return position; }
		void setPosition(glm::vec3 position) { this->position = position; }
		
		glm::mat4 calculateViewMatrix() { return glm::lookAt(position, position + front, up); };

		glm::vec3 getUp() const { return up; }
		GLfloat getYaw() const { return yaw; }


	private:
		glm::vec3 position;
		glm::vec3 up;
		glm::vec3 front;
		glm::vec3 right;
		glm::vec3 worldUp;

		GLfloat yaw; // Left and right (X-Axis)
		GLfloat pitch; // Up and down (Y-Axis)

		sf::Vector2<int> lastMousePosition;
		GLfloat movementSpeed;
		GLfloat mouseSensitivity;

		void updateCameraVectors();
};
