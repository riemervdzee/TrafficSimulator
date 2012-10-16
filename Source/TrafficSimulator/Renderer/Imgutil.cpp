#include "Imgutil.h"
#include <iostream>
#include <fstream>
#include <cstring>

// load in a .tga file
bool LoadImageTGA(std::string fileName, TGAFile* tga, bool flipY)
{
	unsigned char header[12];
	unsigned char id; // dummy

	// try opening the tga file
	std::ifstream tgaStream(fileName.c_str(), std::ios::binary);

	// check if we succeeded opening it
	if(!tgaStream.is_open())
	{
		std::cerr << "Error could not load in " << fileName << std::endl;
		return false;
	}

	// read header
	tgaStream.read((char*)&header, 12);

	// read in width and height
	tgaStream.read((char*)&tga->width, sizeof(unsigned short));
	tgaStream.read((char*)&tga->height, sizeof(unsigned short));

	// read in bpp
	tgaStream.read((char*)&tga->Bpp, 1);
	tgaStream.read((char*)&id, 1);

	// calc bytes per pixel
	tga->bytesperpixel = tga->Bpp / 8;
	unsigned char bytespp = tga->bytesperpixel;

	// error check
	if(bytespp != 1 && bytespp != 3 && bytespp != 4)
		return false;

	// calc image size in bytes
	tga->imageSize = tga->width * tga->height * tga->bytesperpixel;

	// read in the color data
	tga->data = new unsigned char[tga->imageSize];
	unsigned char* tempData = new unsigned char[tga->imageSize];
	tgaStream.read((char*)tempData, tga->imageSize);

	// error check
	if(tempData == 0)
		return false;

	// set data
	unsigned char* src = NULL;
	unsigned char* dest = NULL;
	int rowBytes = tga->width * tga->bytesperpixel;

	// flip y axis if we specified it
	if(flipY)
	{
		for(int i = 0; i < tga->height; i++)
		{
			src = tempData + i * rowBytes;
			dest = tga->data + ( tga->height - (i + 1) ) * rowBytes;
			memcpy(dest, src, rowBytes);
		}
	}
	else
	{
		memcpy(tga->data, tempData, tga->imageSize);
	}


	// delete temp data
	delete []tempData;

	return true;
}
