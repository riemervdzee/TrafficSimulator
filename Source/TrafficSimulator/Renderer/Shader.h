/*
 * Author: Mark van der Wal
 * Date: 22-01-2012
 * Descr: Class for handling and creating shaders
 */
#ifndef _SHADER_H_
#define _SHADER_H_

#include "GL/glew.h"
#include <GL/glfw.h>
#include <string>

class ShaderProgram
{
private:
	GLuint mID; // program id
	GLuint mvID; // vertex shader id
	GLuint mfID; // fragment shader id

public:
	ShaderProgram() : mID(0), mvID(0), mfID(0) {}

	// creates the shader program
	GLboolean CreateProgram(const std::string& vertex, const std::string& fragment);
	GLvoid Dispose();

	GLuint GetID() { return mID; }
	GLvoid Bind();
	GLvoid Unbind();

private:
	GLuint CreateShader(GLenum type, const std::string& shaderCode);
};

#endif
