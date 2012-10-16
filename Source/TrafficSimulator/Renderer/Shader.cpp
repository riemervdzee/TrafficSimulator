/*
 * Author: Mark van der Wal
 * Date: 22-01-2012
 * Descr: Class for handling and creating shaders
 */
#include "Shader.h"
#include <cstdio>

void ShaderProgram::Bind()
{
	glUseProgram(mID);
}

void ShaderProgram::Unbind()
{
	glUseProgram(0);
}

void ShaderProgram::Dispose()
{
	glUseProgram(0);

	glDetachShader(mID, mvID);
	glDetachShader(mID, mfID);

	glDeleteShader(mvID);
	glDeleteShader(mfID);

	glDeleteProgram(mID);
}

GLuint ShaderProgram::CreateShader(GLenum type, const std::string& shaderCode)
{
	// create the shader hull
	GLuint id = glCreateShader(type);

	// put the shadercode in it the shader hull
	const GLchar* strCode = shaderCode.c_str();
	glShaderSource(id, 1, &strCode, NULL);

	// compile the shader
	glCompileShader(id);

	// error checking
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if(status == GL_FALSE)
	{
		// get the length of the shader info log
		GLint infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

		// get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(id, infoLogLength, NULL, infoLog);

		// show error
		printf("Shader compile error:\n %s\n", infoLog);

		delete[] infoLog;
		return 0;
	}

	return id;
}

GLboolean ShaderProgram::CreateProgram(const std::string& vertex, const std::string& fragment)
{
	// create vertex shader & fragment shader
	mvID = CreateShader(GL_VERTEX_SHADER, vertex);
	mfID = CreateShader(GL_FRAGMENT_SHADER, fragment);

	// check if shader succeeded compiling
	if(mfID == 0 || mvID == 0)
	{
		glDeleteShader(mvID);
		glDeleteShader(mfID);
		return false;
	}

	// create shader program
	mID = glCreateProgram();
	glAttachShader(mID, mvID);
	glAttachShader(mID, mfID);

	glLinkProgram(mID);

	// error check
	GLint status;
	glGetProgramiv(mID, GL_LINK_STATUS, &status);

	if(status == GL_FALSE)
	{
		GLint logLength;
		glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &logLength);

		GLchar *infoLog = new GLchar[logLength];
		glGetProgramInfoLog(mID, logLength, NULL, infoLog);

		printf("Shader program linking error: %s\n", infoLog);

		delete []infoLog;

		return false;
	}

	return true;
}
