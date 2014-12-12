/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014

*/
#pragma once
#include "Decl.h"
#include "GameMode.h"
#include "DataBase.h"

class Player : public Entity
{
	// players defualt direction when spawwned in
	m_direction  b_direction = eUp;
	
public:
	int p_score = 0;
	State m_state;
//Player constructor
	Player(GameState *a_gs, unsigned a_sprite,
		   float a_x, float a_y, int a_w, int a_h,
		   float a_speed, float a_fDelay, State m_state);
	
	
	void Update(float a_dt);
	
	
	void Draw();
	void DrawScore(int x, int y);
	void Fire();
};