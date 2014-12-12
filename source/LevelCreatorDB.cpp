#include "LevelCreatorDB.h"
#include "LevelFactory.h"
#include <sstream>


char *Level::L_filename = "Level.db";

Level::Level(const char *a_path)
{
	sqlite3_open(a_path, &m_db);

	sqlite3_exec(m_db, "CREATE TABLE IF NOT EXISTS level_objects(type INT, x INT, y INT);", 0, 0, 0);
}

Level::~Level()
{
	sqlite3_close(m_db);
}

void Level::addEntity(int a_type, int a_x, int a_y)
{
	std::stringstream ss;
	ss << "INSERT INTO level_objects(type, x, y) VALUES (" << a_type << ", " << a_x << ", " << a_y << ");";
	sqlite3_exec(m_db, ss.str().c_str(), 0, 0, 0);
}

void Level::Populate()
{
		sqlite3_exec(m_db, "SELECT * FROM level_objects", LevelFactory::FactoryLevelLoadDatabaseCallback, 0, 0);
}