#include "DataBase.h"
#include "GameMode.h"
#include "aie.h"
#include <cstring>
#include <sstream>


ControlObject *ControlManager::s_controls[e_count];

sqlite3 *ControlManager::s_db;

const char ControlManager::s_keys_default[e_count] = { 'W', 'S', 'A', 'D', 'I', 'K', 'J', 'L' };

char ControlManager::s_keys_cache[e_count];

char *ControlManager::s_filename = "Controls.db";


const char *e_control_names[] = 
{
	"Move Up" ,
	"Move Down",
	"Move Left",
	"Move Right",
	"Fire Up",
	"Fire Down",
	"Fire Left",
	"Fire Right"
};


static int FetchControls(void *key_cache, int numArgs, char **data, char**name)
{
	for (int i = 0; i < numArgs; i += 2)
	{
		ControlManager::s_controls[atoi(data[i + 1])]->key = ((char*)key_cache)[atoi(data[i + 1])] = atoi(data[i]);
	}
	return 0;
}

static int TableExists(void *doesExist, int numArgs, char **data, char **name)
{
	*(bool*)doesExist = numArgs;
	return 0;
}

void ControlManager::open()
{
	for (int i = 0; i < e_count; ++i)
	{
		s_controls[i] = new ControlObject
			(e_control_names[i],i,s_keys_default[i], 200 + (i/4)*400, 600 - (i%4)*80, 200, 40);
	}


	sqlite3_open(s_filename, &s_db);

	const char* command = "SELECT * FROM controls;";
	bool exists = false;
	//std::cerr << sqlite3_exec(s_db, command, TableExists, &exists, 0) << std::endl;

	if (!exists)
	{
		//std::cerr << "Doesn't Exist" << std::endl;
		memcpy(s_keys_cache, s_keys_default, e_count * sizeof(char));

		const char* command = "CREATE TABLE controls(key INT, command INT);";
		//std::cerr << sqlite3_exec(s_db, command, 0, 0, 0) << std::endl;

		for (int i = 0; i < e_count; ++i)
		{
			std::stringstream ss;
			ss << "INSERT INTO controls(key,command) VALUES (";
			ss << (int)s_keys_cache[i] << "," << i << ");";

			//std::cerr << sqlite3_exec(s_db, ss.str().c_str(), 0, 0, 0) << std::endl;
		}
	}

	//std::cerr << "Exists" << std::endl;
	const char* command2 = "SELECT * FROM controls;";
	//std::cerr << sqlite3_exec(s_db, command2, FetchControls, s_keys_cache, 0) << std::endl;
}


void ControlManager::changeKey(e_Controls e, char key)
{
	s_keys_cache[e] = key;

	std::stringstream ss;
	ss << "UPDATE controls SET key = " << (int)key << " WHERE command = " << e << ";";
	sqlite3_exec(s_db, ss.str().c_str(), 0, 0, 0); 
}

bool ControlManager::isKeyDown(e_Controls e)
{	
	return IsKeyDown(s_keys_cache[e]);
}

void ControlManager::print()
{
	for (int i = 0; i < e_count; ++i)
	{
		s_controls[i]->update();
	}
}

void ControlManager::close()
{
	sqlite3_close(s_db);

	for (int i = 0; i < e_count; ++i)
	{
		delete s_controls[i];
	}
}