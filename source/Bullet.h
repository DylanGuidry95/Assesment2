/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014
*/

#pragma once
#include "Decl.h"



class Bullet : public Entity
{
//bullet direction
	int b_direction;
	int m_active;
public:

////Bullet constructor
	Bullet(GameState *a_gs, unsigned a_sprite,
		float a_x, float a_y, int a_w, int a_h,
		float a_speed, int a_direction);

	void Update(float a_dt);
	void Draw();
	bool IsActive();
	void kill() { m_active = false; }
};