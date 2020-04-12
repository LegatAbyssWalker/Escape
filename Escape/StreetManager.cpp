#include "StreetManager.h"

StreetManager::StreetManager(GLWindow& window, glm::vec3 streetScaleValue)
	: window(window) {

	// Street
	street = std::make_unique<Entity>(window, WALL_MODEL_LOCATION);
	street->setScale(streetScaleValue);
	street->setModelPosition(glm::vec3(streetScaleValue.x, 0, 0));

	// Finishline
	finishline = std::make_unique<Entity>(window, FINISHLINE_MODEL_LOCATION);
	finishline->setScale(glm::vec3(0.2, 0.3, 0.3));
	finishline->setModelPosition(glm::vec3(street->getSize().x + street->getModelPosition().x, 0, 0));

	// House
	house = std::make_unique<Entity>(window, HOUSE_MODEL_LOCATION);
	house->setScale(glm::vec3(0.5));
	house->setModelPosition(glm::vec3(getLow().x - 1, 0, 0));

	const float zSize[8] = { street->getSize().z, -street->getSize().z,
							 street->getSize().z, -street->getSize().z,
							 street->getSize().z, -street->getSize().z,
							 street->getSize().z, -street->getSize().z
	};

	const float zSizeBench[8] = {
							 street->getSize().z - 0.5, -street->getSize().z + 0.5,
							 street->getSize().z - 0.5, -street->getSize().z + 0.5,
							 street->getSize().z - 0.5, -street->getSize().z + 0.5,
							 street->getSize().z - 0.5, -street->getSize().z + 0.5
	};

	const glm::f32 rotationAngle[8] = { 80, -80,
										80, -80,
										80, -80,
										80, -80
	};

	GLfloat slxPos[8] = { 5, 5, 15, 15, 25, 25, 35, 35 };
	GLfloat bxPos[8]  = { 10, 10, 20, 20, 25, 25, 30, 30 };

	// Streetlamp
	for (int i = 0; i < 8; i++) {
		streetlampVector.emplace_back(new Entity(window, STREETLAMP_MODEL_LOCATION));

		streetlampVector[i]->setModelPosition(glm::vec3(slxPos[i], street->getModelPosition().y, street->getModelPosition().z + zSize[i]));
		streetlampVector[i]->setScale(SCALE_VALUE);
		streetlampVector[i]->setRotation(rotationAngle[i], glm::vec3(0, 1, 0));
	}

	// Benches
	for (int i = 0; i < 8; i++) {
		benchVector.emplace_back(new Entity(window, BENCH_MODEL_LOCATION));
		benchVector[i]->setModelPosition(glm::vec3(bxPos[i], street->getModelPosition().y, street->getModelPosition().z + zSizeBench[i]));
		benchVector[i]->setScale(SCALE_VALUE);
		benchVector[i]->setRotation(-rotationAngle[i], glm::vec3(0, 1, 0));
	}
	
	// Cars
	int carAmount = randomCarAmount[0].getInt(3, 10);

	for (int i = 0; i < carAmount; i++) {
		glm::vec3 carPosition;
		carPosition.x = randomCarPosition[0].getInt(street->getModelPosition().x - street->getSize().x + 3,
											        street->getModelPosition().x + street->getSize().x - 3);
		carPosition.z = randomCarPosition[1].getFloat(zSize[1] + 0.5, zSize[0] - 0.5);
		carPosition.y = Y_AXIS_POSITION;

		carVector.emplace_back(new Entity(window, CAR_MODEL_LOCATION));
		carVector[i]->setModelPosition(glm::vec3(carPosition));
		carVector[i]->setScale(SCALE_VALUE);

		glm::f32 rotation = random[0].getFloat(0, 360);
		carVector[i]->setRotation(rotation, glm::vec3(0, 1, 0));
	}

}

void StreetManager::render(const glm::mat4 viewMatrix, const glm::mat4& projection) {
	
	street->render(viewMatrix, projection);
	finishline->render(viewMatrix, projection);
	house->render(viewMatrix, projection);

	for (auto& car : carVector)				  { car->render(viewMatrix, projection); }
	for (auto& streetlamp : streetlampVector) { streetlamp->render(viewMatrix, projection); }
	for (auto& bench : benchVector)			  { bench->render(viewMatrix, projection); }
}
