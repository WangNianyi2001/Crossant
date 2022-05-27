#include "Crossant/feature/graphics/3d/shader.hpp"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glew.h>
#include <sstream>
#include <iostream>

using namespace Crossant::Graphics::Graphics3D;

Shader::~Shader() {
	if(id == 0)
		return;
	glDeleteProgram(id);
}

void PrintCompileError(
	GLuint id,
	void(*sizeGetter)(GLuint, GLenum, GLint *),
	void(*msgGetter)(GLuint, GLsizei, GLsizei *, char *)
) {
	GLint size;
	sizeGetter(id, GL_INFO_LOG_LENGTH, &size);
	std::string msg;
	msg.resize(size);
	msgGetter(id, size, NULL, (char *)msg.c_str());
	std::cerr << msg << std::endl;
}

Shader* Shader::FromStream(std::istream vertexStream, std::istream fragmentStream) {
	// Load code
	if(!vertexStream || !fragmentStream)
		return nullptr;
	std::stringstream vertexSS, fragmentSS;
	vertexSS << vertexStream.rdbuf();
	fragmentSS << vertexStream.rdbuf();
	std::string vertexS = vertexSS.str(), fragmentS = fragmentSS.str();
	char const *vertexC = vertexS.c_str(), *fragmentC = fragmentS.c_str();

	// Compile
	GLint success;

	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexC, NULL);
	glCompileShader(vertexID);
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
	if(!success) {
		PrintCompileError(vertexID, glGetShaderiv, glGetShaderInfoLog);
		return nullptr;
	}

	GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentC, NULL);
	glCompileShader(fragmentID);
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
	if(!success) {
		PrintCompileError(fragmentID, glGetShaderiv, glGetShaderInfoLog);
		return nullptr;
	}

	// Create program
	id = glCreateProgram();
	glAttachShader(id, vertexID);
	glAttachShader(id, fragmentID);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success) {
		PrintCompileError(id, glGetProgramiv, glGetProgramInfoLog);
		return nullptr;
	}

	// Release
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void Shader::Use() const {
	glUseProgram(id);
}