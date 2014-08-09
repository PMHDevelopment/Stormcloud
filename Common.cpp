#include "Common.h"
#include "Exceptions.h"

using namespace Stormcloud;

GLuint Common::createShader(GLenum eShaderType, const std::string &fileSource) {
	GLuint shader = glCreateShader(eShaderType);
	const char *strFileData = fileSource.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLenth;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLenth);

		GLchar *strInfoLog = new GLchar[infoLogLenth + 1];
		glGetShaderInfoLog(shader, infoLogLenth, NULL, strInfoLog);
		const char *strShaderType = NULL;
		switch (eShaderType) {
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}
		fprintf(stderr, "Compile failure in %s shader: \n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}

GLuint Common::createProgram(const std::vector<GLuint> &shaderList) {
	GLuint program = glCreateProgram();

	for (size_t i = 0; i < shaderList.size(); i++)
		glAttachShader(program, shaderList[i]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLenght;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLenght);

		GLchar *strInfoLog = new GLchar[infoLogLenght + 1];
		glGetProgramInfoLog(program, infoLogLenght, NULL, strInfoLog);

		fprintf(stderr, "Linker error: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (size_t i = 0; i < shaderList.size(); i++)
		glDetachShader(program, shaderList[i]);

	return program;

}

std::string Common::LoadFile(const char *file) {
	std::ifstream in;
	in.open(file);
	return static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str();
}

GLFWwindow* Common::createWindow(int width, int height, const char* title, GLFWmonitor *monitor, GLFWwindow *share) {
	GLFWwindow* window;
	window = glfwCreateWindow(width, height, title, monitor, share); // Create window
	if (!window){ glfwTerminate(); return NULL; } //Window not created so exit.
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (!glload::LoadFunctions()) { //Load OpenGL functions
		return NULL;
	}
	return window;
}

GLFWwindow* Common::initAndCreateWindow(int width, int height, const char* title, GLFWmonitor *monitor, GLFWwindow *share) {
	if (!glfwInit()) { throw GLFWFailedToInitializeException; return NULL; } //Exit with an error.
	GLFWwindow* window;
	window = glfwCreateWindow(width, height, title, monitor, share); // Create window
	if (!window){ glfwTerminate(); return NULL; } //Window not created so exit.

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (!glload::LoadFunctions()) { //Load OpenGL functions
		return NULL;
	}
	return window;
}