/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014
*/

#pragma once
#include <map>
#include <string>
#include "decl.h"
class AssetManager
{
	//handles allthe texture creation
	struct TextureData { unsigned  m_handle, m_width, m_height; }; 
	
	//Maps for setting sprites to a specific class
	static std::map<std::string, TextureData> s_textures;
	AssetManager() {}

public:
	static void Draw(const char *name, int x, int y); 
	static void LoadSprite(const char *name, const char *path, int w, int h);

	static int GetHeight(const char *name); 
	static int GetWidth(const char *name);

	static void DeleteAll();
};
