#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace Stormcloud {


#pragma once
class MatrixStack
{
public:
	MatrixStack();
	MatrixStack(const glm::mat4 &initialMatrix);
	~MatrixStack();
	void pop();
	void push();
	glm::mat4 top();
	void MatrixStack::setIdentity();
	void applyMatrix(const glm::mat4 &matrix);
	MatrixStack& operator*=(const glm::mat4 &matrix);

	//Rotation, translation, and scale.
	void rotateX(float ang);
	void rotateY(float ang);
	void rotateZ(float ang);
	void rotate(glm::vec3 axes, float ang);
	void rotateRadians(const glm::vec3 axes, float angRad);

	//Scale
	void scale(const glm::vec3 &scaleVec);
	void scale(float scaleX, float scaleY, float scaleZ);
	void scale(float uniformScale);

	//Translate
	void translate(const glm::vec3 offsetVec);
	void translate(float transX, float transY, float transZ);

private:
	glm::mat4 currentMatrix;
	float matrices[160]; //Max is 10 matrices
	int firstIndexUsable;
};

}