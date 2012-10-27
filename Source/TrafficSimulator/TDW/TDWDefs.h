#ifndef _TDWDEFS_H_
#define _TDWDEFS_H_

#include <map>

// typedefs
typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;
typedef long			s32;
typedef float			f32;

enum TDWFLAGS : u8
{
	SCALE = 1,
	EXTENSION = 2,
	HIDDEN = 4,
	LIGHTMAP = 16
};

// ##### BASIC TYPES ########
struct Color3 // RGB color 24 bit
{
	u8 r;
	u8 g;
	u8 b;
};

struct Vec2 // 2d vector
{
	f32 x;
	f32 y;
};

struct Vec3 // 3d vector
{
	f32 x;
	f32 y;
	f32 z;
};

struct Vec4 // 4d vector
{
	f32 x;
	f32 y;
	f32 z;
	f32 w;
};

// ##### HEADER ########
struct TDWHeader
{
	u16 mapVersion;
	u8  mapFlags;
	s32 nameCount;
	s32 nameOffset;
	s32 objectCount;
	s32 objectOffset;
};

// ##### MATERIAL ########
struct TDWMaterial
{
	u8	flags;
	s32 groupName;
	s32 objectName;
	s32 extensionName;
};

// ##### LIGHTMAP ########
struct TDWLightmap
{
	u8		flags;
	u8		resolution;
	s32		format;
	Color3* data;
};

// ##### ENTITIES ########
struct TDWEntity
{
	u8					flags;
	Vec3				position;
	s32					keyCount;
	std::map<s32, s32>	KeyValueMap;
};

// ##### BRUSH ########
struct TDWIndex
{
	u8		vertex;
	Vec2	texCoord;
	Vec2	lightmapCoord;
};

struct TDWFace
{
	u8		flags;
	Vec4	plane;

	// texture data
	Vec2	texPos;
	Vec2	texScale;
	Vec2	texRot;
	Vec4	UTexPlane;
	Vec4	VTexPlane;

	f32		luxelSize;
	s32		smoothIndex;
	s32		materialIndex;
	s32		lightmapIndex;

	// indices
	u8		indexCount;
	TDWIndex		*indices;
};

struct TDWBrush
{
	// bookkeeping
	u8						flags;
	s32						keyCount;
	std::map<s32, s32>		KeyValueMap;

	// brush data
	Color3					brushColor;
	u8						vertexCount;
	Vec3					*vertices;
	u8						faceCount;
	TDWFace					*faces;
};

// ##### TERRAIN ########
struct TDWTerrainLayer
{
	s32	name;
	s32	materialIndex;
	u8	*alphaMap; // only if( layerCount > 1 )
};

struct TDWTerrain
{
	u8 flags;
	Vec3	position;
	f32		width;
	f32		height;
	s32		name;
	s32		resolution;
	s32		sectors;
	s32		detailLevels;
	f32		lightmapResolution;
	s32		layerCount;

	// terrain data
	Color3			*luxelColors; // resolution ^ 2
	f32				*terrainHeightData; // (resolution + 1) ^ 2
	TDWTerrainLayer	*layers; // layers[layerCount]
};

#endif //_TDWDEFS_H_