#pragma once
#include <vector>
#include "AIE.h"
#include "Decl.h"



class LevelFactory : public Entity
{
	LevelFactory()
	{ 
	playerSP == nullptr;
	}

public:

	Entity *playerSP;
	Entity *enemySP;
	Entity *wallSP;
	std::vector<Entity*> objects; // All of the entities in one place!
	

	bool m_selected;
	static LevelFactory &getInstance(); // The singleton instance

	//Callback function used by the level loader to instruct the factory which entities to load in.
	static int FactoryLevelLoadDatabaseCallback(void *u, int nArgs, char **data, char **cname);

	// Returns a reference to the vector storing all of the entity pointers
	std::vector<Entity*> &getObjects();

	// Deletes all of the entities
	void clearAll();

	void update(float a_dt);

	Entity *SpawnPlayer(float x, float y);
	Entity *SpawnWall(float x, float y);
	Entity *SpawnEnemy(float x, float y);
	Entity *Spawn(int type, float x, float y);
};