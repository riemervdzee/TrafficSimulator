#ifndef TEXTURE_CUBE_H_
#define TEXTURE_CUBE_H_

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <string>
#include <cstdio>
#include "GL/glew.h"
#include <GL/glfw.h>

class TextureCube
{
private:
	std::string mTextures[6];
	GLuint mTextureID;
	GLuint mWidth;
	GLuint mHeight;

public:
	TextureCube():mTextureID(0) {}
	~TextureCube() { Dispose(); }

	// Create texture
	GLvoid LoadTGA(std::string fileName, bool mipmap = false);

	// methods
	inline GLuint GetID() { return mTextureID; }
	inline GLuint GetWidth() { return mWidth; }
	inline GLuint GetHeight() { return mHeight; }
	inline GLvoid Bind()
	{
		if(glIsTexture(mTextureID))
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);
		}
		else
		{
			printf("Not a valid texture name");
		}
	}

	inline GLvoid Unbind() {  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);  }

	inline GLvoid Dispose()
	{
		if(mTextureID != 0)
		{
			Unbind();
			glDeleteTextures(1, &mTextureID);
		}
	}
};

#endif
