#pragma once

// Origin = Mr. Marco

//struct ScoreData // doesn't matter what's in here
//{
//	int score;
//};


typedef int ScoreData;

class ScoreBuffer // Mainly static class for global access
{
	static int m_nScores;		// Number of scores
	static ScoreData *m_scores; // Array of scores
	static const char *m_path;
	ScoreBuffer() {}
public:
	static void load();
	static void draw(int x, int y);
	static void save();
	static void sort();
	static void addScore(ScoreData a_score);
	static void drawGame(int x, int y);
};