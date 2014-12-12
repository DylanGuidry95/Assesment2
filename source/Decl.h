/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014
*/

#pragma once
#include <cmath>
#include <vector>
#include <iterator>
#include "Aie.h"
#include <queue>
/*
	g_ is for global		    (outside of all functions)
	m_ is for member variable   (in a class definition)
	e_ is an external reference (unmanaged pointer- a pointer we won't delete)
	a_ is for argument          (a function parameter)
*/

// These globals are for the screen width and  height.
const int g_w = 1080;
const int g_h = 720;

const int g_maxSprites = 64; // The most number of sprites we can manage.
const int g_maxBullets = 1; // The most number of bullets we can manage.
const int g_maxEnemies = 20; // Most number of Sprites we can manage on screen 
const int g_maxWalls = 30; // Most number of Walls
const int g_maxPlayerSpawns = 1; //Most number of Player Spawns
const int g_maxEnemySpawns = 10; // Most number of enemy spawn points




// Forward Declarations
class LevelFactory;
class Walls;
class AssetManager;
class GameState;
class Player;
class Enemy;
class Bullet;
class DataBase;
class EnemySpawn;
class PlayerSpawn;
class WallsSpawn;
enum State { Dead, Alive };

enum m_direction { eUp, eDown, eLeft, eRight };//Player directions.. For bullet firing

//////Has all the entities shared by all the other groups
class Entity
{
public:
	enum e_Objects{ ePlayer, eEnemy, eWalls, eNone, eCount};
	static Walls *m_Walls[];
	static Player *m_player;
	static std::vector<Bullet*> m_vbullets;
	static Enemy *m_enemy[];
	////////////////////////////////////////Factory
	static std::vector<WallsSpawn*> m_SpWalls;
	static PlayerSpawn *m_SpPlayer[];
	static std::vector<EnemySpawn*> m_SpEnemy;
	///////////////////////////////////////////////////////
	int m_w, m_h; // Dimensions of sprite
	float m_x, m_y; // Position of sprite
	float m_speed; // movement speed
	unsigned m_sprite; 
	char *m_texturename;

	GameState *e_gs;	// Reference pointer to GameState

	float m_fDelay, m_fTimer; // Firing controls
	float m_fSpeed;

	int m_w2; // half width
	int m_h2;  // half height
	int m_pad; // For boundary collision.
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////Distance functions
	float distanceBetween(const Entity *b)
	{
		return sqrt(((m_x - b->m_x) * (m_x - b->m_x)) + ((m_y - b->m_y) * (m_y - b->m_y)));
	}
	///////////////////////////////////////////////
	///////////////Collision function
	bool Collision( const Entity *b)
	{
		return distanceBetween(b) < m_w2 + b->m_w2;
	}

	virtual void Update(float dt) {}
	virtual void draw() {}
};


