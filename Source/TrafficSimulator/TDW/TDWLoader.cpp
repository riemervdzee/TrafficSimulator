#include "TDWLoader.h"
#include "TDWFile.h"
#include <fstream>
#include <cmath>
#include <exception>

// static member
MessageCallback TDWLoader::fpMessageCallback = 0;

// set the callback we will use for messages
void TDWLoader::SetMessageCallback(MessageCallback callback)
{
	TDWLoader::fpMessageCallback = callback;
}

// sends a message to the callback
void TDWLoader::SendMessage(const char* text)
{
	// send message if we have a callback
	if(TDWLoader::fpMessageCallback != 0)
	{
		// let the client handle the message
		TDWLoader::fpMessageCallback(text);
	}
	else
	{
		// print text to the standard output
		printf(text);
	}
}

// load the 3DW file from the harddisk
TDWFile* TDWLoader::LoadFromFile(const char* filePath)
{
	// used variables
	std::ifstream fileStream;
	TDWFile* tdwFile = new TDWFile();
	
	// try to open the file
	fileStream.open(filePath, std::ios_base::binary | std::ios_base::in | std::ios_base::out);
	if( !fileStream.is_open() )
	{
		// return null if the file could not be opened
		SendMessage("File could not be opened!");
		return 0;
	}

	std::string msg(filePath);
	msg += " file opened!\n------------------------------";

	// load in the file
	SendMessage(msg.c_str());

	// load in the header file
	LoadHeader(fileStream, *tdwFile);

	// load name table
	LoadNameTable(fileStream, *tdwFile);

	// load the objects
	LoadObjects(fileStream, *tdwFile);

	fileStream.close();
	return tdwFile;
}

void TDWLoader::LoadHeader(std::ifstream& fileStream, TDWFile& file)
{
	// read into the header structure
	fileStream.seekg(0, std::ios::beg);

	// read version number
	fileStream.read( (char*)&file.mHeader.mapVersion, sizeof(u16));

	// read map flags
	fileStream.read( (char*)&file.mHeader.mapFlags, sizeof(u8));

	// read name count & offset
	fileStream.read( (char*)&file.mHeader.nameCount, sizeof(s32));
	fileStream.read( (char*)&file.mHeader.nameOffset, sizeof(s32));

	// read object count & offset
	fileStream.read( (char*)&file.mHeader.objectCount, sizeof(s32));
	fileStream.read( (char*)&file.mHeader.objectOffset, sizeof(s32));
}

void TDWLoader::LoadNameTable(std::ifstream& fileStream, TDWFile& file)
{
	// variables
	char* nameTableBuffer;
	int curPos = fileStream.tellg();
	int byteSize = 0;

	// get nametable bytesize
	fileStream.seekg(0, std::ios::end);
	byteSize = fileStream.tellg();
	byteSize -= file.mHeader.nameOffset;
	fileStream.seekg( file.mHeader.nameOffset, std::ios::beg);

	// create buffer and fill with data
	nameTableBuffer = new char[byteSize];
	memset( (void*)nameTableBuffer, 0, sizeof(nameTableBuffer) );
	fileStream.read(nameTableBuffer, byteSize);

	// set back to old position
	fileStream.seekg(curPos, std::ios::beg);

	// get all names from the file
	int counter = 0;
	for(int i = 0; i < file.mHeader.nameCount; ++i)
	{
		file.mNameTable.push_back(nameTableBuffer);
		nameTableBuffer = nameTableBuffer + (strlen(nameTableBuffer) + 1); // go the next string, +1 for null terminating character
		counter += (strlen(nameTableBuffer) + 1);
	}
}

void TDWLoader::LoadObjects(std::ifstream& fileStream, TDWFile& file)
{
	// object variables
	s32			nameIndex = 0;
	s32			dataSize = 0;
	std::string objectName;
	
	// iterate over all objects in the file if any
	if( file.mHeader.objectCount < 1)
		return;

	for(int i = 0; i < file.mHeader.objectCount; ++i)
	{
		// read nameindex and datasize
		fileStream.read( (char*)&nameIndex, sizeof(s32));
		fileStream.read( (char*)&dataSize, sizeof(s32));

		// get name from the name table
		objectName = file.mNameTable[ (nameIndex - 1)];

		if(objectName.compare("visgroup"))
			SendMessage( ("Loading .... " + objectName).c_str() );

		// load all chunks we want to load from the file
		if(objectName.compare("material") == 0)
		{
			LoadMaterial(fileStream, file);
		}
		else if(objectName.compare("lightmap") == 0)
		{
			LoadLightmap(fileStream, file);
		}
		else if(objectName.compare("brush") == 0)
		{
			LoadBrushes(fileStream, file);
		}
		else if(objectName.compare("entity") == 0)
		{
			LoadEntities(fileStream, file);
		}
		else if(objectName.compare("terrain") == 0)
		{
			LoadTerrain(fileStream, file);
		}
		else
		{
			// set pointer in file to correct location
			fileStream.seekg(dataSize , std::ios::cur);
		}
	}
}

void TDWLoader::LoadMaterial(std::ifstream& fileStream, TDWFile& file)
{
	TDWMaterial material;
	memset( (void*)&material, 0, sizeof(TDWMaterial) );

	// load members from the file
	fileStream.read( (char*)&material.flags, sizeof(u8));
	fileStream.read( (char*)&material.groupName, sizeof(s32));
	fileStream.read( (char*)&material.objectName, sizeof(s32));
	material.extensionName = 0;

	// check if the material has an extension
	if( material.flags & TDWFLAGS::EXTENSION)
	{
		// also load in extension index
		fileStream.read( (char*)material.extensionName, sizeof(s32));
	}

	// add material to the file
	file.mMaterials.push_back(material);
}

void TDWLoader::LoadLightmap(std::ifstream& fileStream, TDWFile& file)
{
	TDWLightmap lightmap;
	memset( (void*)&lightmap, 0, sizeof(TDWLightmap) );

	// load members from the file
	fileStream.read( (char*)&lightmap.flags, sizeof(u8));
	fileStream.read( (char*)&lightmap.resolution, sizeof(u8));
	fileStream.read( (char*)&lightmap.format, sizeof(s32));

	// read in the data
	u32 resolution = powf(2, lightmap.resolution);
	u32 dataSize = resolution * resolution;
	u32 bytes = dataSize * sizeof(Color3);

	lightmap.data = new Color3[dataSize];
	fileStream.read( (char*)lightmap.data, bytes );

	// add material to the file
	file.mLightmaps.push_back(lightmap);
}

void TDWLoader::LoadBrushes(std::ifstream& fileStream, TDWFile& file)
{
	TDWBrush brush;
	s32 keyIndex, keyValue;
	
	// load members from the file
	fileStream.read( (char*)&brush.flags, sizeof(u8));
	fileStream.read( (char*)&brush.keyCount, sizeof(s32));

	// add key value pairs
	for(int i = 0; i < brush.keyCount; ++i)
	{
		fileStream.read( (char*)&keyIndex, sizeof(s32));
		fileStream.read( (char*)&keyValue, sizeof(s32));

		// add to map
		brush.KeyValueMap[keyIndex] = keyValue;
	}

	// skip groups and visgroups
	fileStream.seekg(8, std::ios::cur);

	// load members from the file
	fileStream.read( (char*)&brush.brushColor, sizeof(Color3));
	fileStream.read( (char*)&brush.vertexCount, sizeof(u8));

	// load in all vertices
	brush.vertices = new Vec3[ brush.vertexCount ];
	fileStream.read( (char*)brush.vertices, sizeof(Vec3) * brush.vertexCount);

	// load in all the faces
	fileStream.read( (char*)&brush.faceCount, sizeof(u8));
	brush.faces = new TDWFace[brush.faceCount];
	for(int i = 0; i < brush.faceCount; ++i)
	{
		TDWFace& face = brush.faces[i];

		// read in all face members
		fileStream.read( (char*)&face.flags, sizeof(u8));
		fileStream.read( (char*)&face.plane, sizeof(Vec4));
		fileStream.read( (char*)&face.texPos, sizeof(Vec2));
		fileStream.read( (char*)&face.texScale, sizeof(Vec2));
		fileStream.read( (char*)&face.texRot, sizeof(Vec2));
		fileStream.read( (char*)&face.UTexPlane, sizeof(Vec4));
		fileStream.read( (char*)&face.VTexPlane, sizeof(Vec4));
		fileStream.read( (char*)&face.luxelSize, sizeof(f32));
		fileStream.read( (char*)&face.smoothIndex, sizeof(s32));
		fileStream.read( (char*)&face.materialIndex, sizeof(s32));

		// if it has a lightmap read it in which one
		if( face.flags & TDWFLAGS::LIGHTMAP )
		{
			fileStream.read( (char*)&face.lightmapIndex, sizeof(s32));
		}
		else
		{
			face.lightmapIndex = 0;
		}

		// read in index count & load in all indices
		fileStream.read( (char*)&face.indexCount, sizeof(u8));
		face.indices = new TDWIndex[face.indexCount];

		for(int i = 0; i < face.indexCount; ++i)
		{
			fileStream.read( (char*)&face.indices[i].vertex, sizeof(u8));
			fileStream.read( (char*)&face.indices[i].texCoord, sizeof(Vec2));

			// if it has a lightmap read in it's lightmapcoords
			if( face.flags & TDWFLAGS::LIGHTMAP )
			{
				fileStream.read( (char*)&face.indices[i].lightmapCoord, sizeof(Vec2));
			}
			else
			{
				face.indices[i].lightmapCoord.x = 0;
				face.indices[i].lightmapCoord.y = 0;
			}
		}
		
	}

	// add brush to the file
	file.mBrushes.push_back(brush);
}

void TDWLoader::LoadEntities(std::ifstream& fileStream, TDWFile& file)
{
	TDWEntity entity;
	s32 keyIndex, keyValue;
	entity.flags = 0;
	entity.keyCount = 0;
	memset( (void*)&entity.position, 0, sizeof(Vec3));

	// load members from the file
	fileStream.read( (char*)&entity.flags, sizeof(u8));
	fileStream.read( (char*)&entity.position, sizeof(Vec3));
	fileStream.read( (char*)&entity.keyCount, sizeof(s32));

	// add key value pairs
	for(int i = 0; i < entity.keyCount; ++i)
	{
		fileStream.read( (char*)&keyIndex, sizeof(s32));
		fileStream.read( (char*)&keyValue, sizeof(s32));

		// add to map
		entity.KeyValueMap[keyIndex] = keyValue;
	}

	// skip groups and visgroups
	fileStream.seekg(8, std::ios::cur);

	// add to the list
	file.mEntities.push_back(entity);
}

void TDWLoader::LoadTerrain(std::ifstream& fileStream, TDWFile& file)
{
	TDWTerrain terrain;
	memset( (void*)&terrain, 0, sizeof(TDWTerrain));

	// load members from the file
	fileStream.read( (char*)&terrain.flags, sizeof(u8));
	fileStream.read( (char*)&terrain.position, sizeof(Vec3));
	fileStream.read( (char*)&terrain.width, sizeof(f32));
	fileStream.read( (char*)&terrain.height, sizeof(f32));
	fileStream.read( (char*)&terrain.name, sizeof(s32));
	fileStream.read( (char*)&terrain.resolution, sizeof(s32));
	fileStream.read( (char*)&terrain.sectors, sizeof(s32));
	fileStream.read( (char*)&terrain.detailLevels, sizeof(s32));
	fileStream.read( (char*)&terrain.lightmapResolution, sizeof(f32));
	fileStream.read( (char*)&terrain.layerCount, sizeof(s32));

	// calc data
	u32 resolution = terrain.resolution;
	u32 dataSize = resolution * resolution;
	u32 bytes = dataSize * sizeof(Color3);

	// allocate luxel array and initialize
	terrain.luxelColors = new Color3[dataSize];
	fileStream.read( (char*)terrain.luxelColors, bytes);

	// allocate terrain data aray and initialize
	terrain.terrainHeightData = new f32[(resolution + 1) * (resolution + 1)];
	fileStream.read( (char*)terrain.terrainHeightData, (resolution + 1) * (resolution + 1) * sizeof(f32));

	// create layers and initialize
	if( terrain.layerCount > 0)
	{
		terrain.layers = new TDWTerrainLayer[ terrain.layerCount ];
		memset( (void*)terrain.layers, 0, sizeof(TDWTerrainLayer) * terrain.layerCount);
		for( int i = 0; i < terrain.layerCount; ++i)
		{
			TDWTerrainLayer* layer = &terrain.layers[i];

			// init values
			fileStream.read( (char*)&layer->name, sizeof(s32));
			fileStream.read( (char*)&layer->materialIndex, sizeof(s32));

			// init alpha map if this is not the first layer
			if( i > 0 )
			{
				// allocate memory for alpha map and initialize
				layer->alphaMap = new u8[(resolution + 1) * (resolution + 1)];
				fileStream.read( (char*)layer->alphaMap, (resolution + 1) * (resolution + 1));
			}
		}
	}

	// add to the list
	file.mTerrains.push_back(terrain);
}