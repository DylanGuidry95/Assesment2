/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014
*/

#include "Enemy.h"
#include "AssetManager.h"
#include "GameState.h"
#include "Bullet.h"
#include "Walls.h"

Enemy *Entity::m_enemy[20]; 

Enemy::Enemy(GameState *a_gs, unsigned a_sprite,
	float a_x, float a_y, int a_w, int a_h,
	float a_speed, State m_state)
	
{
	m_w = a_w;
	m_h = a_h;
	m_speedY = m_speedX = a_speed;
	m_sprite = a_sprite;
	m_texturename = "enemy";
	e_gs = a_gs;
	m_x = a_x;
	m_y = a_y;
	m_w2 = m_w / 2; // x +/- m_w2 gives us the left/right side of the ship
	m_h2 = m_h / 2;
	m_state = Alive;
}

void Enemy::Update(float a_dt)
{
	///////Autoamted movement for the enemy
	m_x += m_speedX * a_dt;
	m_y += m_speedY * a_dt;
	///////Makes it so when the enemey reaches the border it bounces off in another direction like a screen saver
	if (m_x < 60 || m_x > 1020) m_speedX *= -1;	
	if (m_y < 40 || m_y > 680) m_speedY *= -1;
	if (m_y < 40) m_y = 40;
	if (m_y > 680) m_y = 680;
	if (m_x < 60) m_x = 60;
	if (m_x > 1020) m_x = 1020;
	
	
	////////////Enemy Collison with bullets
	for (int i = 0; i < m_vbullets.size(); ++i)
	{
		if (m_vbullets[i] && m_vbullets[i]->IsActive())
			if (Collision(m_vbullets[i]))
			{
   			m_state = Dead;
			m_vbullets[i]->kill();
        	m_player->p_score += 1;
			}
	}
	/////Enmey Collision with Walls
	//for (int i = 0; i < g_maxWalls; ++i)
	//{
	//	if (m_Walls[i] && m_Walls[i]->IsActive())
	//		if (Collision(m_Walls[i]))
	//		{
	//			m_speedX *= -1;
	//			m_speedY *= -1;
	//		}
	//}
}

void Enemy::Draw()
{
	AssetManager::Draw(m_texturename, m_x, m_y);
}