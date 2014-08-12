#include "Camera.h"


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

glm::mat4 Camera::calculateViewMatrix(bool negateY) {
	direction = glm::vec3(
		cos(Rotation.y) * sin(Rotation.x),
		0,
		cos(Rotation.y) * cos(Rotation.x));

	glm::vec3 right = glm::vec3(
		sin(Rotation.x - 3.14f / 2.0f),
		0,
		cos(Rotation.x - 3.14f / 2.0f)
		);

	glm::vec3 up = glm::cross(right, direction);

	viewMatrix = glm::lookAt(Position, Position + sphericalToCartesian(negateY), up);
	return viewMatrix;
}

glm::mat4 Camera::getViewMatrix() {
	return viewMatrix;
}