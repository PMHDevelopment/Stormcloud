#pragma once

#include "Program.h"
#include <string>
#include <fstream>
#include <vector>

using namespace Stormcloud;

Program::Program(GLuint id)
{
	this->id = id;
	glGenVertexArrays(1, &vao);
}

void Program::use() {
	glUseProgram(id);
}

void Program::useWithVAO() {
	glUseProgram(id);
	glBindVertexArray(vao);
}

void Program::setVboData(GLuint Type) {
	if (vbo == 0) { glGenBuffers(1, &vbo); }
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(dataBuffer), dataBuffer, Type);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] & dataBuffer;
}

void Program::setEboData(GLuint Type) {
	if (ebo == 0) { glGenBuffers(1, &ebo); }
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, Type);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete[] & indexData;
}

GLuint CreateProgram(const std::vector<GLuint> &shaderList) {
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

GLuint createShader(GLenum eShaderType, const std::string &fileSource) {
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