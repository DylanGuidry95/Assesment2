#include "LevelFactory.h"
#include "Player.h"
#include "Enemy.h"
#include "AssetManager.h"
#include "Walls.h"
#include "SpawnPoints.h"
#include <iostream>

LevelFactory &LevelFactory::getInstance()
{
	static LevelFactory instance;
	return instance;
}

int LevelFactory::FactoryLevelLoadDatabaseCallback(void *u, int nArgs, char **data, char **cname)
{
	// TODO: Spawn entities instead of printing their information to the screen.
	//std::cout << Entity::eTypeName(atoi(data[0])) << " x: " << atoi(data[1]) << " y: " << atoi(data[2]) << std::endl;

	LevelFactory::
		getInstance().Spawn(atoi(data[0]), (atoi(data[1])), (atoi(data[2])));

	return 0;
}


void LevelFactory::clearAll()
{
	// TODO: Delete/clear all the entities out of the vector. Emptying it out completely.
	for each(Entity *e in objects)
		delete e;

	objects.clear();
}

std::vector<Entity*>&LevelFactory::getObjects()
{
	return objects;
}

void LevelFactory::update(float a_dt)
{
	//DrawString("[?] Help", 10, 30);
	//while (IsKeyDown('H'))
	//	{
	//		DrawString("[P] Player Spawn, [E] Enemy Spawn, [W] Walls Spawn", 10, 40);
	//	} 
	/////////////////////////////////////////////Player Sapwn points
	if (IsKeyDown('P') && !SpawnBase::s_lock) //Player Key
	{
		if (playerSP != nullptr) delete playerSP;
		playerSP = new PlayerSpawn(ePlayer, 0, g_w / 2, g_h / 2, 64, 32);
		//objects.push_back();
	}
	if (playerSP)
	{
		playerSP->Update(a_dt);
		playerSP->draw();
	}

	////////////////////////////////////////////////Enemy Sapwn Points
	if (IsKeyDown('E') && !SpawnBase::s_lock) //Enemy Key
	{
		if (enemySP) delete enemySP;
		objects.push_back(new EnemySpawn(eEnemy, 0, g_w / 2, g_h / 2, 64, 32));
		objects.back();
	}
	for each(auto object in objects)
	{
		object->draw();
		object->Update(a_dt);
	}

/////////////////////////////////////////////////////Walls Sapwn Points
	if (IsKeyDown('W') && !SpawnBase::s_lock) //Walls Key
	{
		if (wallSP) delete wallSP;
		objects.push_back(new WallsSpawn(eWalls, 0, g_w / 2, g_h / 2, 64, 32));
		objects.back();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
Entity *LevelFactory::SpawnPlayer(float x, float y)
{
	return new PlayerSpawn(ePlayer, 0, x, y, 64, 32);
}

Entity *LevelFactory::SpawnEnemy(float x, float y)
{
	objects.push_back(new EnemySpawn(eEnemy ,0, x, y, 64, 32));
	return objects.back();
}

Entity *LevelFactory::SpawnWall(float x, float y)
{
	objects.push_back(new WallsSpawn(eWalls ,0, x, y, 64, 32));
	return objects.back();
}

Entity *LevelFactory::Spawn(int type, float x, float y)
{
	switch (type)
	{
	case SpawnBase::ePlayer:
	{return SpawnPlayer(x, y); }

	case SpawnBase::eWalls:
	{return SpawnWall(x, y); }

	case SpawnBase::eEnemy:
	{return SpawnEnemy(x, y); }
	}
}