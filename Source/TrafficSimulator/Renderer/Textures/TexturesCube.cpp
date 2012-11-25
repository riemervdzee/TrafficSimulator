/*
 * Author: Mark van der Wal
 * Date: 07-08-2012
 * Descr: class representing a Cube texture
 */
#include "TextureCube.h"
#include "../Imgutil.h"

void TextureCube::LoadTGA(std::string filename, bool mipmap)
{
	// used vars
	TGAFile tga[6];
	memset(tga, 0, sizeof(TGAFile) * 6);
	GLenum internForm;
	GLenum externForm;

	if(mTextureID != 0)
		Dispose();

	// fill in texture names
	mTextures[0] = filename + "_rt.tga";
	mTextures[1] = filename + "_lf.tga";
	mTextures[2] = filename + "_up.tga";
	mTextures[3] = filename + "_dn.tga";
	mTextures[4] = filename + "_ft.tga";
	mTextures[5] = filename + "_bk.tga";

	// load each file
	for(int i = 0; i < 6; i++)
	{
		if( !LoadImageTGA(mTextures[i], &tga[i], true))
		{
			printf("Could not load %s\n", mTextures[i].c_str());

			// delete previous loaded tga
			for(int j = 0; j < i;j++)
			{
				delete []tga[i].data;
			}
			return;
		}
	}

	// set data
	mWidth = tga[0].width;
	mHeight = tga[0].height;

	// create texture and bind it
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);

	// check which formats to use
	if(tga[0].bytesperpixel == 1)
	{
		internForm = GL_LUMINANCE;
		externForm = GL_LUMINANCE;
	}
	else if(tga[0].bytesperpixel == 3)
	{
		internForm = GL_RGB;
		externForm = GL_BGR;
	}
	else if(tga[0].bytesperpixel == 4)
	{
		internForm = GL_RGBA;
		externForm = GL_BGRA;
	}

	// set texture state
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// check if we want to generate mipmaps
	if(mipmap)
	{
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	// put the data inside
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, internForm, mWidth, mHeight, 0, externForm, GL_UNSIGNED_BYTE, tga[1].data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, internForm, mWidth, mHeight, 0, externForm, GL_UNSIGNED_BYTE, tga[0].data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, internForm, mWidth, mHeight, 0, externForm, GL_UNSIGNED_BYTE, tga[2].data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, internForm, mWidth, mHeight, 0, externForm, GL_UNSIGNED_BYTE, tga[3].data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, internForm, mWidth, mHeight, 0, externForm, GL_UNSIGNED_BYTE, tga[4].data);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, internForm, mWidth, mHeight, 0, externForm, GL_UNSIGNED_BYTE, tga[5].data);


	// unbind
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	//free memory
	for(int i = 0; i < 6; i++)
	{
		delete []tga[i].data;
	}
}