#pragma once
#include <string>
struct Texture
{
	Texture(unsigned int inID, std::string inPath) : ID(inID), Path(inPath) {}
	unsigned int ID;
	std::string Path;
};

