#include "SpawnPoints.h"
#include "AssetManager.h"
#include "Decl.h"
PlayerSpawn *Entity::m_SpPlayer[1];

bool SpawnBase::s_lock = false;
bool SpawnBase::IsActive = false;


PlayerSpawn::PlayerSpawn(e_Objects type, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h)
{
	type = ePlayer;
	m_sprite = a_sprite;
	m_texturename = "SpPlayer";
	m_x = a_x;
	m_y = a_y;
	m_w = a_w;
	m_h = a_h;
	SpawnBase::IsActive = false;
	SpawnBase::s_lock = true;
	m_placed = false;
}
void PlayerSpawn::draw()
{	
	AssetManager::Draw(m_texturename, m_x, m_y);
}


void PlayerSpawn::Update(float a_dt)
{
	if (!SpawnBase::IsActive && !m_placed)
	{
		double c_x, c_y;
		GetMouseLocation(c_x, c_y);
		c_y = g_h - c_y + m_h; // mouse and window Ys are inverted

		m_y = c_y;
		m_x = c_x;
		if (GetMouseButtonDown(0))
		{
			m_placed = true;
			SpawnBase::s_lock = false;
			draw();
			SpawnBase::IsActive = true;
		}
	}
}
/////////////////////////////Enemy Spawn////////////////////////////////////////////
std::vector<EnemySpawn*> Entity::m_SpEnemy;
EnemySpawn::EnemySpawn(e_Objects type, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h)
{
	type = eEnemy;
	m_sprite = a_sprite;;
	m_texturename = "SpEnemy";
	m_x = a_x;
	m_y = a_y;
	m_w = a_w;
	m_h = a_h;
	SpawnBase::IsActive = false;
	SpawnBase::s_lock = true;
	m_placed = false;
}

void EnemySpawn::draw()
{
	AssetManager::Draw(m_texturename, m_x, m_y);
}

void EnemySpawn::Update(float a_dt)
{
	if (!SpawnBase::IsActive && !m_placed)
	{
		double c_x, c_y;
		GetMouseLocation(c_x, c_y);
		c_y = g_h - c_y + m_h; // mouse and window Ys are inverted

		m_y = c_y;
		m_x = c_x;
		if (GetMouseButtonDown(0))
		{
			SpawnBase::s_lock = false;
			draw();
			SpawnBase::IsActive = true;
			m_placed = true;
		}
	}
}
/////////////////////////Walls Spawn/////////////////////////////////////////
std::vector<WallsSpawn*>Entity::m_SpWalls;
WallsSpawn::WallsSpawn(e_Objects type, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h)
{
	type = eWalls;
	m_sprite = a_sprite;
	m_texturename = "SpWalls";
	m_x = a_x;
	m_y = a_y;
	m_w = a_w;
	m_h = a_h;
	SpawnBase::IsActive = false;
	SpawnBase::s_lock = true;
	m_placed = false;
}

void WallsSpawn::draw()
{
	AssetManager::Draw(m_texturename, m_x, m_y);
}

void WallsSpawn::Update(float a_dt)
{
	if (!SpawnBase::IsActive && !m_placed)
	{
		double c_x, c_y;
		GetMouseLocation(c_x, c_y);
		c_y = g_h - c_y + m_h; // mouse and window Ys are inverted

		m_y = c_y;
		m_x = c_x;
		if (GetMouseButtonDown(0))
		{
			SpawnBase::s_lock = false;
			draw();
			SpawnBase::IsActive = true;
			m_placed = true;
		}
	}
}