#include "TDWLoader.h"
#include "TDWFile.h"
#include <fstream>
#include <cstring>
#include <cmath>
#include <exception>
#include <iostream>

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
		printf("%s\n", text);
	}
}

// load the 3DW file from the harddisk
TDWFile* TDWLoader::LoadFromFile(const char* filePath)
{
	// used variables
	std::ifstream fileStream;
	TDWFile* tdwFile = new TDWFile();
        memset((void*)tdwFile, 0, sizeof(TDWFile));

	// try to open the file
#ifndef __linux__
	fileStream.open(filePath, std::ios_base::binary | std::ios_base::in);
#else
        fileStream.open(filePath);
#endif
	if( !fileStream.is_open() )
	{
		// return null if the file could not be opened
		SendMessage("File could not be opened!");
		return 0;
	}

	// load in the header file
	LoadHeader(fileStream, *tdwFile);
        SendMessage("Header loaded!\n");

	// load name table
	LoadNameTable(fileStream, *tdwFile);
        SendMessage("Nametable loaded!\n");

	// load the objects
	LoadObjects(fileStream, *tdwFile);
        SendMessage("Objects loaded!\n");

	fileStream.close();
        
        std::string msg(filePath);
	msg += " file loaded!\n------------------------------";

	// load in the file
	SendMessage(msg.c_str());
        
	return tdwFile;
}

void TDWLoader::LoadHeader(std::ifstream& fileStream, TDWFile& file)
{
	// read into the header structure
	fileStream.seekg(0, std::ios::beg);

	// read version number
	fileStream.read( (char*)&file.mHeader.mapVersion, sizeof(u16));
        std::cout << "Bytes read: " << fileStream.gcount() << std::endl;

	// read map flags
	fileStream.read( (char*)&file.mHeader.mapFlags, sizeof(u8));
        std::cout << "Bytes read: " << fileStream.gcount() << std::endl;
                                        
	// read name count & offset
	fileStream.read( (char*)&file.mHeader.nameCount, sizeof(s32));
        std::cout << "Bytes read: " << fileStream.gcount() << std::endl;
	fileStream.read( (char*)&file.mHeader.nameOffset, sizeof(s32));
        std::cout << "Bytes read: " << fileStream.gcount() << std::endl;

	// read object count & offset
	fileStream.read( (char*)&file.mHeader.objectCount, sizeof(s32));
        std::cout << "Bytes read: " << fileStream.gcount() << std::endl;
	fileStream.read( (char*)&file.mHeader.objectOffset, sizeof(s32));
        std::cout << "Bytes read: " << fileStream.gcount() << std::endl;
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

	// counters
	int brushes = 0;
	int materials = 0;
	int lightmaps = 0;
	int entities = 0;
	int terrains = 0;

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

		if(objectName.compare("visgroup") == 0)
		{
		    //SendMessage( ("Loading .... " + objectName).c_str() );
		    file.mGroups++;
		}

		if(objectName.compare("group") == 0)
		{
            file.mGroups++;
		}

		// load all chunks we want to load from the file
		if(objectName.compare("material") == 0)
		{
		    materials++;
			LoadMaterial(fileStream, file);
		}
		else if(objectName.compare("lightmap") == 0)
		{
		    lightmaps++;
			LoadLightmap(fileStream, file);
		}
		else if(objectName.compare("brush") == 0)
		{
		    brushes++;
			LoadBrushes(fileStream, file);
		}
		else if(objectName.compare("entity") == 0)
		{
		    entities++;
			LoadEntities(fileStream, file);
		}
		else if(objectName.compare("terrain") == 0)
		{
		    terrains++;
			LoadTerrain(fileStream, file);
		}
		else
		{
			// set pointer in file to correct location
			fileStream.seekg(dataSize , std::ios::cur);
		}
	}

	// show info about loaded data
	printf("Loaded %d materials\n", materials);
	printf("Loaded %d lightmaps\n", lightmaps);
	printf("Loaded %d entities\n", entities);
	printf("Loaded %d brushes\n", brushes);
	printf("Loaded %d terrains\n", terrains);
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
	if( material.flags & EXTENSION)
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
	u32 bytes = dataSize * sizeof(color3);

	lightmap.data = new color3[dataSize];
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
	fileStream.read( (char*)&brush.brushColor, sizeof(color3));
	fileStream.read( (char*)&brush.vertexCount, sizeof(u8));

	// load in all vertices
	brush.vertices = new vec3[ brush.vertexCount ];
	fileStream.read( (char*)brush.vertices, sizeof(vec3) * brush.vertexCount);

	// scale down vertices
	for(int i = 0; i < brush.vertexCount; ++i)
	{
        brush.vertices[i].x = brush.vertices[i].x / 10.0f;
        brush.vertices[i].y = brush.vertices[i].y / 10.0f;
        brush.vertices[i].z = brush.vertices[i].z / 10.0f;
	}

	// load in all the faces
	fileStream.read( (char*)&brush.faceCount, sizeof(u8));
	brush.faces = new TDWFace[brush.faceCount];
	for(int i = 0; i < brush.faceCount; ++i)
	{
		TDWFace& face = brush.faces[i];

		// read in all face members
		fileStream.read( (char*)&face.flags, sizeof(u8));
		fileStream.read( (char*)&face.plane, sizeof(vec4));
		fileStream.read( (char*)&face.texPos, sizeof(vec2));
		fileStream.read( (char*)&face.texScale, sizeof(vec2));
		fileStream.read( (char*)&face.texRot, sizeof(vec2));
		fileStream.read( (char*)&face.UTexPlane, sizeof(vec4));
		fileStream.read( (char*)&face.VTexPlane, sizeof(vec4));
		fileStream.read( (char*)&face.luxelSize, sizeof(f32));
		fileStream.read( (char*)&face.smoothIndex, sizeof(s32));
		fileStream.read( (char*)&face.materialIndex, sizeof(s32));

		// if it has a lightmap read it in which one
		if( face.flags & LIGHTMAP )
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
			fileStream.read( (char*)&face.indices[i].texCoord, sizeof(vec2));

			// if it has a lightmap read in it's lightmapcoords
			if( face.flags & LIGHTMAP )
			{
				fileStream.read( (char*)&face.indices[i].lightmapCoord, sizeof(vec2));
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
	memset( (void*)&entity.position, 0, sizeof(vec3));

	// load members from the file
	fileStream.read( (char*)&entity.flags, sizeof(u8));
	fileStream.read( (char*)&entity.position, sizeof(vec3));
	fileStream.read( (char*)&entity.keyCount, sizeof(s32));

    // scale down positions
    entity.position.x = entity.position.x / 10.0f;
    entity.position.y = entity.position.y / 10.0f;
    entity.position.z = entity.position.z / 10.0f;

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
	fileStream.read( (char*)&terrain.position, sizeof(vec3));
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
	u32 bytes = dataSize * sizeof(color3);

	// allocate luxel array and initialize
	terrain.luxelColors = new color3[dataSize];
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