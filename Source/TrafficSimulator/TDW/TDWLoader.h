#ifndef _3DWLOADER_H_
#define _3DWLOADER_H_

#include <fstream>

// function pointer for message callback
typedef void (*MessageCallback)(const char*);

class TDWFile;

// handles the loading of 3D world studio files
class TDWLoader
{
public:
	static TDWFile* LoadFromFile(const char* filePath);
	static void SetMessageCallback(MessageCallback callback);

	enum TDWFLAGS
    {
        SCALE = 1,
        EXTENSION = 2,
        HIDDEN = 4,
        LIGHTMAP = 16
    };

private:
	// we do not want to create objects of this class
	TDWLoader();

	// callback for messages
	static MessageCallback fpMessageCallback;

	// methods
	static void SendMessage(const char* text);

	// loading TDW data
	void static LoadHeader(std::ifstream& fileStream, TDWFile& file);
	void static LoadNameTable(std::ifstream& fileStream, TDWFile& file);
	void static LoadObjects(std::ifstream& fileStream, TDWFile& file);

	// load TDW objects
	void static LoadMaterial(std::ifstream& fileStream, TDWFile& file);
	void static LoadLightmap(std::ifstream& fileStream, TDWFile& file);
	void static LoadBrushes(std::ifstream& fileStream, TDWFile& file);
	void static LoadEntities(std::ifstream& fileStream, TDWFile& file);
	void static LoadTerrain(std::ifstream& fileStream, TDWFile& file);
};

#endif // _3DWLOADER_H_
