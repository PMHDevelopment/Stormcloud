#include "MatrixStack.h"

using namespace Stormcloud;

MatrixStack::MatrixStack()
{
	currentMatrix = glm::mat4(1.0f);
	float matrices[160]; //Max is 10 matrices
	firstIndexUsable = 0;
}

MatrixStack::MatrixStack(const glm::mat4 &initialMatrix)
{
	currentMatrix = initialMatrix;
	float matrices[160]; //Max is 10 matrices
	firstIndexUsable = 0;
}


//**Start the awesome stuffs :)

void MatrixStack::push() {
	
	glm::vec4 a = currentMatrix[0];
	glm::vec4 b = currentMatrix[1];
	glm::vec4 c = currentMatrix[2];
	glm::vec4 d = currentMatrix[3];
	matrices[firstIndexUsable] = currentMatrix[0].x;matrices[firstIndexUsable+1] = currentMatrix[0].y;matrices[firstIndexUsable+2] = currentMatrix[0].z;matrices[firstIndexUsable+3] = currentMatrix[0].w;
	matrices[firstIndexUsable+4] = currentMatrix[1].x; matrices[firstIndexUsable + 5] = currentMatrix[1].y; matrices[firstIndexUsable + 6] = currentMatrix[1].z; matrices[firstIndexUsable + 7] = currentMatrix[1].w;
	matrices[firstIndexUsable+8] = currentMatrix[2].x; matrices[firstIndexUsable + 9] = currentMatrix[2].y; matrices[firstIndexUsable + 10] = currentMatrix[2].z; matrices[firstIndexUsable + 11] = currentMatrix[2].w;
	matrices[firstIndexUsable+12] = currentMatrix[3].x; matrices[firstIndexUsable + 13] = currentMatrix[3].y; matrices[firstIndexUsable + 14] = currentMatrix[3].z; matrices[firstIndexUsable + 15] = currentMatrix[3].w;
	firstIndexUsable += 16;
}

void MatrixStack::pop() {
	firstIndexUsable -= 16;

	currentMatrix = glm::mat4(
		glm::vec4(matrices[firstIndexUsable], matrices[firstIndexUsable + 1], matrices[firstIndexUsable + 2], matrices[firstIndexUsable + 3]),
		glm::vec4(matrices[firstIndexUsable + 4], matrices[firstIndexUsable + 5], matrices[firstIndexUsable + 6], matrices[firstIndexUsable + 7]),
		glm::vec4(matrices[firstIndexUsable + 8], matrices[firstIndexUsable + 9], matrices[firstIndexUsable + 10], matrices[firstIndexUsable + 11]),
		glm::vec4(matrices[firstIndexUsable + 12], matrices[firstIndexUsable + 13], matrices[firstIndexUsable + 14], matrices[firstIndexUsable + 15]));


}

void MatrixStack::setIdentity() {
	currentMatrix = glm::mat4(1.0f);
}

void MatrixStack::applyMatrix(const glm::mat4 &matrix) {
	currentMatrix *= matrix;
}

MatrixStack& MatrixStack::operator*=(const glm::mat4 &matrix) {
	return MatrixStack(currentMatrix * matrix);
}

glm::mat4 MatrixStack::top() {
	return currentMatrix;
}

//Rotation, translation, and scale.

void MatrixStack::rotateX(float ang) {
	currentMatrix = glm::rotate(currentMatrix, ang, glm::vec3(1, 0, 0));
}

void MatrixStack::rotateY(float ang) {
	currentMatrix = glm::rotate(currentMatrix, ang, glm::vec3(0, 1, 0));
}

void MatrixStack::rotateZ(float ang) {
	currentMatrix = glm::rotate(currentMatrix, ang, glm::vec3(0, 0, 1));
}

void MatrixStack::rotate(glm::vec3 axes, float ang) {
	currentMatrix = glm::rotate(currentMatrix, ang, axes);
}

//Scale

void MatrixStack::scale(const glm::vec3 &scaleVec) {
	currentMatrix = glm::scale(currentMatrix, scaleVec);
}

void MatrixStack::scale(float scaleX, float scaleY, float scaleZ) {
	currentMatrix = glm::scale(currentMatrix, glm::vec3(scaleX, scaleY, scaleZ));
}

void MatrixStack::scale(float uniformScale) {
	currentMatrix = glm::scale(currentMatrix, glm::vec3(uniformScale, uniformScale, uniformScale));
}

//Translate

void MatrixStack::translate(const glm::vec3 offsetVec) {
	currentMatrix = glm::translate(currentMatrix,offsetVec);
}
void MatrixStack::translate(float transX, float transY, float transZ) {
	currentMatrix = glm::translate(currentMatrix, glm::vec3(transX,transY,transZ));
}




MatrixStack::~MatrixStack()
{
}
