#include <iostream>
#include "sqlite3.h"
#include <string>
#include <iostream>
#include "sqlite3.h"
#include <string>
#include "decl.h"
#include "TextObj.h"
#pragma once

enum e_Controls
{
	e_up, e_down, e_left, e_right,
	e_fireUp, e_fireDown, e_fireLeft, e_fireRight, 
	e_count
};


class ControlManager 
{
	static char s_keys_cache[e_count];
	static const char s_keys_default[e_count];
	static sqlite3 *s_db;
	static char *s_filename;


public:
	static ControlObject *s_controls[e_count];
	static void changeKey(e_Controls e, char key);
	static void restore(e_Controls e);
	static bool isKeyDown(e_Controls e);
	static void open();
	static void close();
	static void print();
};