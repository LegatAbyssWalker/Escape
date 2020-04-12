#include "Player.h"

Player::Player(GLWindow& window, glm::vec3 cameraPosition, glm::mat4 projection)
	: window(window) {
	// Camera
	camera = Camera(cameraPosition, glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, (MOVEMENT_SPEED / 3), 0.3f);


	// Bush
	bush = std::make_unique<Entity>(window, BUSH_MODEL_LOCATION);
	bush->setModelPosition(camera.getPosition());
	bush->setScale(glm::vec3(0.5));
	bush->setRotation(1, glm::vec3(0, 1, 0));
}

void Player::mouseUpdate(Wheel wheel) {
	if (wheel != Wheel::WHEEL_STATIC) {
		if (wheel == Wheel::WHEEL_UP)   { rotationAmount += 0.1; }
		if (wheel == Wheel::WHEEL_DOWN) { rotationAmount -= 0.1; }
	}
}

void Player::keyboardUpdate(Movement movement, GLfloat deltaTime) {
	// Camera event updates
	camera.processKeyboard(movement, deltaTime);
}


void Player::update() {
	camera.processMouseMovement(window);
	bush->setModelPosition(glm::vec3(camera.getPosition().x, camera.getPosition().y - 0.5, camera.getPosition().z));
	bush->setRotation(rotationAmount, glm::vec3(0, 1, 0));
}

void Player::render(const glm::mat4 viewMatrix, const glm::mat4& projection) {
	bush->render(viewMatrix, projection);
}

bool Player::boundsZ(std::unique_ptr<Entity>& street) {
	if (camera.getPosition().z >= street->getSize().z ||
		camera.getPosition().z <= -street->getSize().z) {

		return true;
	}
	return false;
}
