/*
Creator: Dylan Gudiry
Credit : Dylan Gudiry
Date: 10/29/2014

*/
#include "Player.h"
#include "GameState.h"
#include "AssetManager.h"
#include "Enemy.h"
#include "GameMode.h"
#include <iostream>

Player *Entity::m_player;

Player::Player(GameState *a_gs, unsigned a_sprite, float a_x, float a_y, int a_w, 
	int a_h, float a_speed, float a_fDelay, State m_state)
	
{
	//Setup our variables
	m_state = Alive;
	m_w = a_w;
	m_h = a_h;
	m_speed = a_speed;
	m_sprite = a_sprite;
	m_fSpeed = 400;		 // This is for our shot speed
	m_fDelay = a_fDelay; // Firing delay
	m_fTimer = 0;        // Firing timer

	m_texturename = "player";
	e_gs = a_gs;
	m_x = a_x;
	m_y = a_y;
	m_w2 = m_w / 2; // x +/- m_w2 gives us the left/right side of the ship
	m_h2 = m_h / 2;

	if (e_gs) m_pad = e_gs->GetPadding(); // only use padding if e_gs isn't null
	else m_pad = 0; //otherwise we have no padding, use screen dimensions
}											

void Player::Fire()
{
	if (m_fTimer > m_fDelay) // What are we checking for here? what are these variables for?
	{
		m_fTimer = 0;
		e_gs->SpawnBullet(m_x, m_y, m_fSpeed, b_direction);
	}
}


void Player::Update(float a_dt)
{
	m_fTimer += a_dt; // Why are we incrementing m_fTimer
	
////Player movement controls
	if (ControlManager::isKeyDown(e_up)){ m_y += m_speed * a_dt; }
	if (ControlManager::isKeyDown(e_down)){ m_y -= m_speed * a_dt; }
	if (ControlManager::isKeyDown(e_left)){ m_x -= m_speed * a_dt; }
	if (ControlManager::isKeyDown(e_right)){ m_x += m_speed * a_dt; }
////Indie fire controls sugsted by Shelby
	if (ControlManager::isKeyDown(e_fireUp)){ b_direction = eUp; Fire(); }
	if (ControlManager::isKeyDown(e_fireDown)){ b_direction = eDown; Fire(); }
	if (ControlManager::isKeyDown(e_fireLeft)){ b_direction = eLeft; Fire(); }
	if (ControlManager::isKeyDown(e_fireRight)){ b_direction = eRight; Fire(); }
		

	// Check to see if we hit a boundary
	if (m_x < 0 + (m_pad + m_w2)) m_x = 0 + (m_pad + m_w2);
	if (m_x > g_w - (m_pad + m_w2)) m_x = g_w - (m_pad + m_w2);
	if (m_y < 0 + (m_pad + m_h2)) m_y = 0 + (m_pad + m_h2);
	if (m_y > g_h - (m_pad + m_h2)) m_y = g_h - (m_pad + m_h2);

	for (int i = 0; i < g_maxEnemies; ++i)
	{
		if (m_enemy[i])
		{
			if (Collision(m_enemy[i]))
			{
				//m_player = nullptr;
				//delete m_player;
				currentstate = eEndGame;
			}
		}
	}

}
void Player::Draw()
{
	AssetManager::Draw(m_texturename, m_x, m_y);
}

