#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glload\gl_3_3.h>
#include <glload\gl_load.hpp>
#include <GLFW\glfw3.h>
namespace Stormcloud {
	#pragma once
	class Camera
	{
	public:
		Camera(glm::mat4* per, glm::vec2 rot = glm::vec2(), glm::vec3 pos = glm::vec3());
		glm::mat4 getViewMatrix();
		glm::mat4 calculateViewMatrix();
		glm::vec2 Rotation;
		glm::vec3 Position; 
		glm::vec3 getRightVector();
		glm::vec3 sphericalToCartesian(bool negateY = false);
	private:
		glm::mat4* projectionMatrix;
		glm::mat4 viewMatrix;
		glm::vec3 direction;
		glm::vec3 right;
	};
}
