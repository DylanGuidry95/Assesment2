/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014
*/

#include "Bullet.h"
#include "Player.h"
#include "decl.h"
#include "AssetManager.h"
#include <iostream>

std::vector <Bullet*> Entity::m_vbullets;

Bullet::Bullet(GameState *a_gs, unsigned a_sprite,
	float a_x, float a_y, int a_w, int a_h,
	float a_speed, int a_direction)
	
{
	m_active = true;
	m_speed = a_speed;
	m_w = a_w;
	m_h = a_h;
	m_sprite = a_sprite;
	b_direction = a_direction;
	m_texturename = "shot";
	e_gs = a_gs;
	m_x = a_x;
	m_y = a_y;

	m_w2 = a_w / 2;
}

void Bullet::Update(float a_dt)
{

	//uses the enum for direction to decide which direction the bullet is fired and is moving
	switch (b_direction)
	{
	case eUp:	 m_y += m_speed * a_dt; break; 
	case eDown:	 m_y -= m_speed * a_dt; break;
	case eLeft:	 m_x -= m_speed * a_dt; break;
	case eRight: m_x += m_speed * a_dt; break;
	}
}

void Bullet::Draw()
{
	AssetManager::Draw(m_texturename, m_x, m_y);
}


bool Bullet::IsActive()
{
	///////Checks to see if a bullet is active by checking to see if it is withing the game border
	return m_y > 0 && m_y < g_h && m_active;
}