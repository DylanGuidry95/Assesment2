#pragma once
#include "sqlite3.h"



class Level
{
	sqlite3 *m_db;

public:
	static char *L_filename;

	Level(const char *a_path);

	
	~Level();


	void addEntity(int a_type, int a_x, int a_y);


	void Populate();
};