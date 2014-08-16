#include <GL\glew.h>
#include <string>
#include <fstream>
#include <vector>
#pragma once
namespace Stormcloud {
	class Program
	{
	public:
		Program(GLuint id);
		GLuint id, ebo, vbo, vao;
		float dataBuffer[1];
		int indexData[1];
		void use();
		void useWithVAO();
		void setVboData(GLuint Type);
		void setEboData(GLuint Type);

	};
}

