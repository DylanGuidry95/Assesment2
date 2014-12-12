#include "Decl.h"
#pragma once

class Walls : public Entity
{
	int m_active;
public:

	Walls(GameState *a_gs, unsigned a_sprite, float a_x, float a_y, 
		int a_w, int a_h);
	void Draw();
	bool IsActive();
};