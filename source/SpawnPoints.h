#pragma once
#include "Decl.h"


class SpawnBase : public Entity
{
public:
	static bool s_lock;
	bool m_placed;
	static bool IsActive;
};


class PlayerSpawn : public SpawnBase
{
public:
	PlayerSpawn(e_Objects type, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h);
	void draw();
	void Update(float a_dt);
};


class EnemySpawn : public SpawnBase
{
public:
	EnemySpawn(e_Objects type, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h);
	void draw();
	void Update(float a_dt);
	void EnemySP(int x, int y);
};


class WallsSpawn : public SpawnBase
{
public:
	WallsSpawn(e_Objects type, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h);
	void draw();
	void Update(float a_dt);
	void WallsSP(int x, int y);
};