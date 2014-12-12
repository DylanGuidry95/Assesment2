
/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014
*/
#include "AssetManager.h"
#include "Aie.h"

///Singleton
std::map<std::string, AssetManager::TextureData> AssetManager::s_textures;

//////////////////////////////////////////////////Draws everything to the screen
void AssetManager::Draw(const char *name, int x, int y)
{
	if (s_textures.count(name) > 0)
	{
		MoveSprite(s_textures[name].m_handle, x, y);
		DrawSprite(s_textures[name].m_handle);
	}
}
////////////////////////////Creates sprites when called 
void AssetManager::LoadSprite(const char *name, const char *path, int w, int h)
{
	if (s_textures.count(name) > 0)
		DestroySprite(s_textures[name].m_handle);

	TextureData t;
	t.m_handle = CreateSprite(path, w, h, true);
	t.m_width = w;
	t.m_height = h;
	s_textures[name] = t;
}
/////////////////////////////////////////////////////Gets Width adn height of objects 
/////////////////////////to determine collision
int AssetManager::GetHeight(const char *name)
{
	if (s_textures.count(name) > 0)
		return s_textures[name].m_height;
	else return -1;
}

int AssetManager::GetWidth(const char *name)
{
	if (s_textures.count(name) > 0)
		return s_textures[name].m_width;
	else return -1;
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Delets everything
void AssetManager::DeleteAll()
{
	for each(auto t in s_textures)
		DestroySprite(t.second.m_handle);
}