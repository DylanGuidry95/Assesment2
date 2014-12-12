/*
Creator: Dylan Guidry
Credit : Dylan Guidry
Date: 10/29/2014
*/

#if !defined(OSX)
	#include <crtdbg.h>
#endif

#include "Aie.h"
#include "Decl.h"
#include "GameState.h"
#include "AssetManager.h"
#include "Player.h"
#include "GameMode.h"
#include "ScoreBuffer.h"
#include "Enemy.h"
#include "DataBase.h"
#include "LevelCreatorDB.h"
#include "LevelFactory.h"
//#include "Cursor.h"


GameMode currentstate = eMenu;

int main(int argc, char* argv[])
{
	Initialise(g_w, g_h, false, "PvE"); //Suggested by Zac
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));

	////////////////////////////////Sprite Management
	AssetManager::LoadSprite("player" ,"./images/cannon.png", 64, 32); //Player
	AssetManager::LoadSprite("shot", "./images/invaders/invaders_5_00.png", 10, 14); //Bullet
	AssetManager::LoadSprite("enemy", "./images/invaders/invaders_1_00.png", 64, 32); //Enemy
	AssetManager::LoadSprite("walls", "./images/crate_sideup.png", 64, 32); //walls
	AssetManager::LoadSprite("SpWalls", "./images/SpWall.png", 64, 32); //Spwalls
	AssetManager::LoadSprite("SpPlayer", "./images/SpPlayer.png", 64, 32); //SpPlayer
	AssetManager::LoadSprite("SpEnemy", "./images/SpEnemy.png", 64, 32); //SpEnemy
	//////////////////////////////GameStates
	GameState myGame(20);
	ScoreData t;
	/////////////////////////////////Level Editor
	LevelFactory &myLevel = LevelFactory::getInstance();
	/////////////////////////////////////Game loop
	ControlManager::open();
	ScoreBuffer::load();
	do
	{
		ClearScreen();
		float dt = GetDeltaTime();
		switch (currentstate)
		{
		case eMenu:
		{
			DrawString("[P]Lay", g_w / 2, g_h / 2 + 60);
			DrawString("[C]ontrols", g_w / 2, g_h / 2 - 60);
			DrawString("[H]igh Scores", g_w / 2, g_h / 2);
			DrawString("[L]evel Creator", g_w / 2, g_h / 2 - 120);
			DrawString("[E]xit", g_w / 2, g_h / 2 - 180);
			if (IsKeyDown('P')) { currentstate = eGame; }
			if (IsKeyDown('H')) { currentstate = eScores; }
			if (IsKeyDown('E')) { currentstate = eExit; }
			if (IsKeyDown('C')) { currentstate = eControls; }
			if (IsKeyDown('L')) { currentstate = eLevelCreator; }
		}break;
		case eLevelCreator:
		{
			//DrawString("WIP", g_w / 2, g_h / 2);
			myLevel.update(dt);
			DrawString("[M]enu", g_w / 2, g_h / 2 );
			if (IsKeyDown('M')) { currentstate = eMenu; }
		}break;
		//////////////////////////////////////////////////////////////////////////////////
		case eControls:
		{
			DrawString("Controls", g_w / 2, g_h / 2 + 300);
			////////////////////////////////////////////////////////
			ControlManager::print();
			DrawString("[R]estore Defaults", g_w / 2, g_h / 2 - 80);
			DrawString("[M]enu", g_w / 2, g_h / 2 - 120);
			if (IsKeyDown('M') && ControlObject::selected == false) { currentstate = eMenu; }

		}break;
		////////////////////////////////////////////////////////////////////////////////////////
		case eGame:
		{
			DrawLine(0, 15, g_w, 15, SColour(0xFF, 0xFF, 0xFF, 0xFC));
			DrawLine(0, 705, g_w, 705, SColour(0xFF, 0xFF, 0xFF, 0xFC));
			DrawLine(1060, 0, g_w, 150000, SColour(0x00, 0x00, 0xFF, 0xFC));
			DrawLine(20, 0, g_w, 1500000, SColour(0x00, 0x00, 0xFF, 0xFC));
			myGame.Update(dt);
			myGame.Draw();
			if (IsKeyDown('O')){ currentstate = ePause; }
		}break;
		case eEndGame:
			t = { myGame.m_player->p_score };
			ScoreBuffer::addScore(t);
			myGame.reset();
			currentstate = eLost;
			break;
		case eLost:
		{
			DrawString("[H]ighScores", g_w / 2, g_h / 2 + 120);
			DrawString("[M]enu", g_w / 2, g_h / 2 + 60);
			DrawString("[E]xit", g_w / 2, g_h / 2 - 60);
			if (IsKeyDown('E')) { currentstate = eExit; }
			if (IsKeyDown('H')) { currentstate = eScores; }
			if (IsKeyDown('M')) { currentstate = eMenu; }		
			
		} break;
		case ePause:
		{
			DrawString("[R]esume", g_w / 2, g_h / 2);
			DrawString("[M]enu", g_w / 2, g_h / 2 + 60);
			DrawString("[E]xit", g_w / 2, g_h / 2 - 60);
			if (IsKeyDown('R')) { currentstate = eGame; }
			if (IsKeyDown('M')) { currentstate = eMenu; }
			if (IsKeyDown('E')) { currentstate = eExit; }
		}break;
		case eScores:
		{
			ScoreBuffer::draw(g_w/2, 500);
			DrawString("[M]ain Menu", 100, 100);
			if (IsKeyDown('M')){ currentstate = eMenu; }
		}break;		
		};
	} while (FrameworkUpdate() == false && currentstate != eExit);
	ControlManager::close();
	ScoreBuffer::save();
	Shutdown();

	return 0;

}
