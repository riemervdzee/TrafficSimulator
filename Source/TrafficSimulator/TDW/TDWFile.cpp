#include "TDWFile.h"

TDWFile::~TDWFile()
{
	// clear lightmap data if any
	for(unsigned int i = 0; i < mLightmaps.size(); ++i)
	{
		if( mLightmaps[i].data )
			delete []mLightmaps[i].data;
	}

	// clear brushes & faces
	for(unsigned int i = 0; i < mBrushes.size(); ++i)
	{
		TDWBrush& brush = mBrushes[i];

		// clear memory for the vertices
		if( brush.vertices )
			delete []brush.vertices;

		// iterate over the faces
		for(int y = 0; y < brush.faceCount; ++y)
		{
			TDWFace& face = brush.faces[y];

			// clear memory of the indices
			if( face.indices )
				delete []face.indices;
		}

		// clear memory of faces
		if( brush.faces )
			delete []brush.faces;
	}

	// clear terrains
	for(unsigned int i = 0; i < mTerrains.size(); ++i)
	{
		// clear luxel colors if it has any
		if(mTerrains[i].luxelColors)
		{
			delete []mTerrains[i].luxelColors;
		}

		// clear terrain height data if it has any
		if(mTerrains[i].terrainHeightData)
		{
			delete []mTerrains[i].terrainHeightData;
		}

		// clear layer alpha maps if it has any
		if(mTerrains[i].layerCount > 1) // we need to delete layers with alpha maps
		{
			// iterate all layers for this terrain that have an alpha map
			for(int y = 1; y < mTerrains[i].layerCount; ++y)
			{
				// delete alpha map for this layer
				if(mTerrains[i].layers[y].alphaMap)
					delete []mTerrains[i].layers[y].alphaMap;
			}
		}

		// clear layers if any
		if( mTerrains[i].layers && mTerrains[i].layerCount > 0)
			delete []mTerrains[i].layers;
	}
}