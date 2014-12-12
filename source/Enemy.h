/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014
*/

#pragma once
#include "Decl.h"
#include "Bullet.h"
#include "Player.h"

class Enemy : public Entity
{
	float m_speedY;
	float m_speedX;
public:
	State m_state;
	

///Enemy constructor
	Enemy(GameState *a_gs, unsigned a_sprite,
		float a_x, float a_y, int a_w, int a_h,
		float a_speed, State m_state);

	void Update(float a_dt);
	void Draw();
};