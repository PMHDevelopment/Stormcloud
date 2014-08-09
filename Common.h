#include <glload\gl_3_3.h>
#include <glload\gl_load.hpp>
#include <GLFW\glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#pragma once
namespace Stormcloud {
	class Common
	{
	public:
		static GLuint createShader(GLenum eShaderType, const std::string &fileSource);
		static GLuint createProgram(const std::vector<GLuint> &shaderList);
		static std::string Common::LoadFile(const char *file);
		static GLFWwindow* initAndCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
		static GLFWwindow* createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	};
}
