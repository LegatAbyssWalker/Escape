#include "Officers.h"

Officers::Officers(GLWindow& window, std::string const& filePath, std::unique_ptr<StreetManager>& manager)
	: model(filePath, window), Object(window) {

	officerSign = random[1].getInt(0, 1);
}

void Officers::update(GLfloat deltaTime, std::unique_ptr<Player>& player, bool useCameraPosition) {
	if (useCameraPosition) { playerXYZ = player->getCamera().getPosition(); }
	else				   { playerXYZ = player->getBush()->getModelPosition(); }

	playerUp = player->getCamera().getUp();
}

void Officers::render(const glm::mat4 viewMatrix, const glm::mat4& projection) {
	program->useProgram();

	// Model matrix
	glm::mat4 modelMatrix(1.f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, scaleValue);
	modelMatrix = glm::rotate(modelMatrix, getRotationAngle(), getRotationAxis());

	// Uniforms
	program->setMat4("model", modelMatrix);
	program->setMat4("view", viewMatrix);
	program->setMat4("projection", projection);

	// Model rendering
	model.renderModel(program);
}

void Officers::updateRotation() {
	glm::f32 prevAngle = getRotationAngle();
	
	switch (officerSign) {
		case 0: { prevAngle += 0.03; break; }
		case 1: { prevAngle -= 0.03; break; }
	}
	setRotation(prevAngle, glm::vec3(0, 1, 0));
}

void Officers::calculateMovement() {
	glm::vec3 playerPosition = playerXYZ;
	glm::vec3 friendPosition = getModelPosition();

	directionalVector = friendPosition - playerPosition;
}

void Officers::moveOfficer(GLfloat generalSpeed) {
	move(glm::normalize(-directionalVector) * glm::vec3(generalSpeed));
}

bool Officers::isColliding(std::unique_ptr<Player>& player, bool useCameraPosition) {
	glm::vec3 playerPosition;
	glm::vec3 playerSize = player->getBush()->getSize();

	if (useCameraPosition) { playerPosition = player->getCamera().getPosition(); }
	else				   { playerPosition = player->getBush()->getModelPosition(); }

	bool collisionX = playerPosition.x + playerSize.x >= getModelPosition().x &&
		getModelPosition().x + getSize().x >= playerPosition.x;

	bool collisionZ = playerPosition.z + playerSize.z >= getModelPosition().z &&
		getModelPosition().z + getSize().z >= playerPosition.z;

	return collisionX && collisionZ;
}
