#include <glm\glm.hpp>

#pragma once
class Renderable
{
public:
	Renderable();
	~Renderable();
	void Render();
private:
	int start, size;
	glm::vec3 Position; //Once we have physics we will create sub objects of this.
	
};

