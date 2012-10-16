#include "Util.h"
#include <fstream>

bool LoadTextFile(const std::string& fileName, std::string& buffer)
{
	std::ifstream file;
	std::string line;

	// try to open the file
	file.open(fileName.c_str());

	if(	!file.is_open() )
	{
		file.close();
		printf("Could not open file: %s\n", fileName.c_str());
		return false;
	}

	// load in the file
	while( std::getline(file, line) )
	{
		buffer += line + '\n';
	}
	file.close();

	return true;
}
