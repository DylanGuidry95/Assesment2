/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014

*/
#include "GameState.h"
#include "Player.h"
#include "AssetManager.h"
#include "Bullet.h"
#include "Enemy.h"
#include "ScoreBuffer.h"
#include "Walls.h"
#include <queue>

int GameState::GetPadding() { return m_padding; }
/////////////Creats the padding for all the sprites to set up the collison with the 
/////////////border of the screen
GameState::GameState(int a_padding)
{
	m_padding = a_padding;

	if (m_player) delete m_player;
	m_player = new Player(this, 0
		, g_w/2, g_w / 2, 64, 32, 150, 0.50f, Alive);

	for (int i = 0; i < g_maxEnemies; ++i)
	{
		if (m_enemy[i]) delete Entity::m_vbullets[i];
		m_enemy[i] = nullptr;
	}

	for (int i = 0; i < g_maxEnemies; ++i)
	m_enemy[i] = new Enemy(this, g_h / 2
			, g_w / 2 * i, 40 * i, 64, 32, 150, Alive);

	//for (int i = 0; i < g_maxWalls; i++)
	//	m_Walls[i] = new Walls(this, 0, g_w / 2 , g_h / 2 , 64, 32);
}


void GameState::reset()
{
	if (m_player) delete m_player;
	m_player = new Player(this, 0
		, g_w / 2, g_h / 2 - 300, 64, 32, 150, 0.25f, Alive);

	for (int i = 0; i < g_maxEnemies; ++i)
	{
		if (m_enemy[i]) delete Entity::m_enemy[i];
		m_enemy[i] = nullptr;
	}

	for (int i = 0; i < g_maxEnemies; ++i)
	m_enemy[i] = new Enemy(this, g_h / 2, g_w / 2 * i, 40 * i, 64, 32, 150, Alive);
	for (int i = 0; i < g_maxEnemies; ++i)
	m_enemy[4] = new Enemy(this, g_h / 7, g_w / 8 * i, 40 * i, 64, 32, 150, Alive);

	for (int i = 0; i < g_maxWalls; i++)
	{
		m_Walls[1] = new Walls(this, 0, (g_w / 2) / 2, (g_h / 2) / 2, 64, 32);
	}
}
/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////Update functions
void GameState::Update(float a_dt)
{
///////////////////////////Player movment
	if (m_player)
		m_player->Update(a_dt); 
	
///////////////////////////Bullet movement

//	for (auto it = m_vbullets.begin(); it != m_vbullets.end(); it++)
//	{
		//(*it) = nullptr;
//	}

	auto it = m_vbullets.begin();
	while (it != m_vbullets.end())
	{
		if ((*it)->IsActive())
		{
			(*it)->Update(a_dt);
			it++;
		}
		else
		{
			delete (*it);
			it = m_vbullets.erase(it);
		}
	}
//////////////////////////Enemy Movement
	for (int i = 0; i < g_maxEnemies; ++i)
		if (m_enemy[i])
			m_enemy[i]->Update(a_dt);

	for (int i = 0; i < g_maxEnemies; ++i)
		if (m_enemy[i] && m_enemy[i]->m_state == Dead)
	{
		delete m_enemy[i];
		m_enemy[i] = new Enemy(this, g_h / 6, g_w / 7 * i, 40 * i, 64, 32, 150, Alive);
	}
}
/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////Draws everytying to the screen
void GameState::Draw()
{
////////////////////////Player
	if (m_player) m_player->Draw();

/////////////////////////Enemy
	for (int i = 0; i < g_maxEnemies; ++i)
		if (m_enemy[i])
			m_enemy[i]->Draw();
////////////////////////Bullet
	for each(auto bullet in m_vbullets)
		bullet->Draw();
///////////////////////Walls
	//for (int i = 0; i < g_maxWalls; ++i)
	//	if (m_Walls[i])
	//		m_Walls[i]->Draw();
}
//////////////////////////////////////////////////////Spawn bullets 
	
void GameState::SpawnBullet(int a_x, int a_y, float a_speed, int a_direction)
{
	Entity::m_vbullets.push_back(new Bullet(this, 0, a_x, a_y, 10, 14, a_speed, a_direction));

/////The useless try catch statement 
	int i = 1;
		try
		{
			if (i = 1)
				throw i;
		}
		catch (int i)
		{
			std::cout << "Die You Scum"<< std::endl;
		}
}

///////////////////////////////////////////////////////Spawn Walls
//void GameState::SpawnWalls(int a_x, int a_y)
//{
//	for (int i = 0; i < g_maxWalls; ++i)
//	{
//			m_Walls[i] = new Walls(this, 0, a_x, a_y, 64, 32);
//			return;
//	}
//}

////////////////////////////////////////////////////////Spawn Enemies
void GameState::SpawnEnemy(int a_x, int a_y, float a_speed, State m_state)
{
	for (int i = 0; i < g_maxEnemies; ++i) ///////checks if max enemy is reached
		/////////If under max spawns more Enemeies when one is killed
	{
		if (!m_enemy[i] || !m_enemy[i]->m_state == Dead)
		{
			if (m_enemy[i] && m_enemy[i]->m_state == Dead)
			{
				delete m_enemy[i];
			}
			m_enemy[i] = new Enemy(this, 0, a_x, a_y, 64, 32, a_speed, Alive);
			return;
		}
	}
	
}
/////////////////////////////////////////////////////////////////////////////
///////////////////////////////Deletes everything
GameState::~GameState()
{
	if (m_player)
		delete m_player;

	for (int i = 0; i < g_maxEnemies; ++i)////////Checks for Enemies and if any deletes them
		if (m_enemy[i])
			delete m_enemy[i];

	//for (int i = 0; i < g_maxWalls; ++i)////////Checks for Walls and if any deletes them
	//	if (m_Walls[i])
	//		delete m_Walls[i];
}