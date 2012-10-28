#ifndef _TDWDEFS_H_
#define _TDWDEFS_H_

#include <map>

// typedefs
typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;
typedef long			s32;
typedef float			f32;


// ##### BASIC TYPES ########
struct color3 // RGB color 24 bit
{
	u8 r;
	u8 g;
	u8 b;
};

struct vec2 // 2d vector
{
	f32 x;
	f32 y;
};

struct vec3 // 3d vector
{
	f32 x;
	f32 y;
	f32 z;
};

struct vec4 // 4d vector
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
	color3* data;
};

// ##### ENTITIES ########
struct TDWEntity
{
	u8					flags;
	vec3				position;
	s32					keyCount;
	std::map<s32, s32>	KeyValueMap;
};

// ##### BRUSH ########
struct TDWIndex
{
	u8		vertex;
	vec2	texCoord;
	vec2	lightmapCoord;
};

struct TDWFace
{
	u8		flags;
	vec4	plane;

	// texture data
	vec2	texPos;
	vec2	texScale;
	vec2	texRot;
	vec4	UTexPlane;
	vec4	VTexPlane;

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
	color3					brushColor;
	u8						vertexCount;
	vec3					*vertices;
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
	vec3	position;
	f32		width;
	f32		height;
	s32		name;
	s32		resolution;
	s32		sectors;
	s32		detailLevels;
	f32		lightmapResolution;
	s32		layerCount;

	// terrain data
	color3			*luxelColors; // resolution ^ 2
	f32				*terrainHeightData; // (resolution + 1) ^ 2
	TDWTerrainLayer	*layers; // layers[layerCount]
};

#endif //_TDWDEFS_H_
