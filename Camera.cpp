#include "Camera.h"

using namespace Stormcloud;

Camera::Camera(glm::mat4* per, glm::vec2 rot, glm::vec3 pos)
{
	projectionMatrix = per;
	Rotation = rot;
	Position = pos;
}

glm::vec3 Camera::sphericalToCartesian(bool negateY) {
	if (negateY)
		return glm::vec3(
		cos(Rotation.y) * sin(Rotation.x),
		sin(Rotation.y),
		cos(Rotation.y) * cos(Rotation.x));
	return glm::vec3(
		cos(Rotation.y) * sin(Rotation.x),
		0,
		cos(Rotation.y) * cos(Rotation.x));
}

glm::mat4 Camera::calculateViewMatrix() {
	direction = glm::vec3(
		cos(Rotation.y) * sin(Rotation.x),
		sin(Rotation.y),
		cos(Rotation.y) * cos(Rotation.x));

	right = glm::vec3(
		sin(Rotation.x - 3.14f / 2.0f),
		0,
		cos(Rotation.x - 3.14f / 2.0f)
		);

	glm::vec3 up = glm::cross(right, direction);

	viewMatrix = glm::lookAt(Position, Position + direction, up);
	return viewMatrix;
}

glm::vec3 Camera::getRightVector() {
	return right;
}

glm::mat4 Camera::getViewMatrix() {
	return viewMatrix;
}