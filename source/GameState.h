#pragma once
#include "Decl.h"



class GameState : public Entity
{
	int m_padding;	 // Padding + g_w are used to determine movement boundaries	
	

public:

	GameState(int a_padding);
	~GameState();

	int GetPadding();
	void SpawnWalls(int a_x, int a_y);
	void SpawnBullet(int a_x, int a_y, float a_speed, int a_direction);
	void SpawnEnemy(int a_x, int a_y, float a_speed, State m_state);
	void reset();
	void Update(float a_dt); //Gathers all the update fuctions in one place 
	void Draw(); //Draw Everything to the screen
};