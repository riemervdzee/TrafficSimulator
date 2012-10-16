#ifndef _IMGUTIL_H_
#define _IMGUTIL_H_

#include <string>
#include <cstring>

// tga file
struct TGAFile
{
	unsigned char bytesperpixel;
	unsigned int imageSize;
	unsigned short width;
	unsigned short height;
	unsigned char Bpp;
	unsigned char* data;
};

// load in a .tga file
bool LoadImageTGA(std::string fileName, TGAFile* tga, bool flipY = false);

#endif
