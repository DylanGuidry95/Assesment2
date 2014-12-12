#include "Walls.h"
#include "Enemy.h"
#include "AssetManager.h"

Walls *Entity::m_Walls[20];

Walls::Walls(GameState *a_gs, unsigned a_sprite, float a_x, float a_y, 
	int a_w, int a_h)
{
	m_active = true;
	m_w = a_w;
	m_h = a_h;
	m_x = a_x;
	m_y = a_y;
	m_texturename = "walls";
	m_w2 = a_w / 2;
	m_h2 = a_h / 2;
}

void Walls::Draw()
{
	AssetManager::Draw(m_texturename, m_x, m_y);
}

bool Walls ::IsActive()
{
	///////Checks to see if a wall is active by checking to see if it is withing the game border
	return m_y > 0 && m_y < g_h && m_active;
}