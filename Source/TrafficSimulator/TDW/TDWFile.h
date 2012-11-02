#ifndef _TDWFILE_H_
#define _TDWFILE_H_

#include <string>
#include <vector>

#include "TDWDefs.h"
#include <cstring>

class TDWLoader;

// class representing the whole .3dw file
class TDWFile
{
	friend class TDWLoader;
public:
	TDWFile()
	{
		// zero out header struct
		memset((void*)&mHeader, 0, sizeof(mHeader));
		mGroups = 0;
	}
	~TDWFile();

	// Header members
	TDWHeader GetHeader() { return mHeader; }

	// Name table members
	std::vector<std::string>& GetNameTable() { return mNameTable; }
	std::string GetNameByIndex(u32 index)
	{
	    if(index < 0 || index >= mNameTable.size())
            return std::string("no name found!");
        else
            return mNameTable[index];
    }

	// Material members
	std::vector<TDWMaterial>& GetMaterials() { return mMaterials; }
	TDWMaterial GetMaterialByIndex(u32 index);

	// Lightmap members
	std::vector<TDWLightmap>& GetLightmaps() { return mLightmaps; }
	TDWLightmap GetLightmapByIndex(u32 index);

	// Entities members
	std::vector<TDWEntity>& GetEntities() { return mEntities; }
	TDWEntity GetEntityByIndex(u32 index);

	// Brushes members
	std::vector<TDWBrush>& GetBrushes() { return mBrushes; }
	TDWBrush GetBrushByIndex(u32 index);

	// Terrains members
	std::vector<TDWTerrain>& GetTerrains() { return mTerrains; }
	TDWTerrain GetTerrainByIndex(u32 index);

	// Group members
	int GetGroupCount(){return mGroups;}

private:
	// bookkeeping
	TDWHeader					mHeader;
	std::vector<std::string>	mNameTable;

	// objects
	std::vector<TDWMaterial>	mMaterials;
	std::vector<TDWLightmap>	mLightmaps;
	std::vector<TDWEntity>		mEntities;
	std::vector<TDWBrush>		mBrushes;
	std::vector<TDWTerrain>		mTerrains;
	int                         mGroups;
};

#endif // _TDWFILE_H_
