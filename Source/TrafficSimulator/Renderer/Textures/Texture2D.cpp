/*
 * Author: Mark van der Wal
 * Date: 3-02-2012
 * Descr: class representing a 2D texture
 */
#include "Texture2D.h"
#include "../Imgutil.h"
#include <cmath>

void Texture2D::LoadFromMemory(const char* source, const char resolution, bool mipmap)
{
    GLenum internForm;
	GLenum externForm;
    internForm = GL_RGB;
    externForm = GL_RGB;

    if(mID != 0)
		Dispose();

    mWidth = mHeight = pow(2, resolution);

    // create texture and bind it
	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

    // put the data inside
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, internForm, mWidth, mHeight, 0, externForm, GL_UNSIGNED_BYTE, source);

	// set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// check if we want to generate mipmaps
	if(mipmap)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::LoadTGA(std::string filename, bool mipmap)
{
	GLenum internForm;
	GLenum externForm;

	if(mID != 0)
		Dispose();

	// used vars
	TGAFile tga;
	memset(&tga, 0, sizeof(tga));

	// load png file
	if( !LoadImageTGA(filename, &tga))
	{
		printf("Could not load %s\n", filename.c_str());
		return;
	}

	// set data
	mWidth = tga.width;
	mHeight = tga.height;

	// create texture and bind it
	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	// check which formats to use
	if(tga.bytesperpixel == 1)
	{
		internForm = GL_LUMINANCE;
		externForm = GL_LUMINANCE;
	}
	else if(tga.bytesperpixel == 3)
	{
		internForm = GL_RGB;
		externForm = GL_BGR;
	}
	else if(tga.bytesperpixel == 4)
	{
		internForm = GL_RGBA;
		externForm = GL_BGRA;
	}

	// put the data inside
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, internForm, mWidth, mHeight, 0, externForm, GL_UNSIGNED_BYTE, tga.data);

	// set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// check if we want to generate mipmaps
	if(mipmap)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	// free memory
	delete []tga.data;
}
