#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat sensitivity)
	: position(position), worldUp(up), yaw(yaw), pitch(pitch), movementSpeed(movementSpeed), mouseSensitivity(sensitivity) {


	front = glm::vec3(0.f, 0.f, -1.f);
	updateCameraVectors();
}

void Camera::processKeyboard(Movement direction, GLfloat deltaTime) {
	front = glm::normalize(glm::vec3(front.x, 0.0, front.z));
	GLfloat velocity = (movementSpeed / 2) * deltaTime;

	// WASD
	if (direction == FORWARD)  { position += front * velocity; }
	if (direction == LEFT)     { position -= right * velocity; }
	if (direction == BACKWARD) { position -= front * velocity; }
	if (direction == RIGHT)    { position += right * velocity; }
}

void Camera::processMouseMovement(GLWindow& window) {
	if (window.getWindow().hasFocus() && sf::Mouse::getPosition(window.getWindow()).y >= 0) {
		auto change = sf::Mouse::getPosition(window.getWindow()) - lastMousePosition;

		change.x *= mouseSensitivity;
		change.y *= mouseSensitivity;


		yaw += change.x;
		pitch += change.y;

		if (pitch > 89.f) {
			pitch = 89.f;
		}
		if (pitch < -89.f) {
			pitch = -89.f;
		}

		// Update front, right, and up vectors when updating euler angles
		updateCameraVectors();

		sf::Mouse::setPosition(sf::Vector2<int>((int)window.getWindow().getSize().x / 2, (int)window.getWindow().getSize().y / 2 ), window.getWindow());
		
		lastMousePosition = sf::Mouse::getPosition(window.getWindow());
	}
}

void Camera::updateCameraVectors() {
	glm::vec3 functionFront;

	functionFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	functionFront.y = sin(glm::radians(-pitch)); // Should be `pitch instead of `-pitch` but it works with `-pitch` so why not. 
	functionFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front   = glm::normalize(functionFront);

	right = glm::normalize(glm::cross(front, worldUp));
	up    = glm::normalize(glm::cross(right, front));
}