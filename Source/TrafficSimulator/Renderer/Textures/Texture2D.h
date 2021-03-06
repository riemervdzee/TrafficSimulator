/*
 * Author: Mark van der Wal
 * Date: 3-02-2012
 * Descr: class representing a 2D texture
 */
#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <string>
#include <cstdio>
#include "GL/glew.h"

// class representing a 2D texture
class Texture2D
{
private:
	GLuint mID;
	GLuint mWidth;
	GLuint mHeight;

public:
	// life circle
	Texture2D():mID(0) {}
	~Texture2D() {} //Dispose(); }

	// create a texture
	GLvoid LoadTGA(std::string filename, bool mipmap = false);
	GLvoid LoadFromMemory(const char* source, const char resolution, bool mipmap = false);

	// methods
	inline GLuint GetID() { return mID; }
	inline GLuint GetWidth() { return mWidth; }
	inline GLuint GetHeight() { return mHeight; }
	inline GLvoid Bind(GLint tex = 0) { glActiveTexture(GL_TEXTURE0 + tex);glBindTexture(GL_TEXTURE_2D, mID); }
	inline GLvoid Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

	// cleans the texture from opengl
	inline GLvoid Dispose()
	{
		if(mID != 0)
		{
			Unbind();
			glDeleteTextures(1, &mID);
			mID = 0;
		}
	}
};

#endif
