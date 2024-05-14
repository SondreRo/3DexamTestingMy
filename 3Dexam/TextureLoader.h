#pragma once


#include <string>

#include "Texture.h"


struct TextureLoader
{
	static Texture* ImportImage(std::string Path);

};

