#include "ScoreBuffer.h"
#include <fstream>
#include "Aie.h"
#include <cstring>


int ScoreBuffer::m_nScores = 0;		// Number of scores
ScoreData *ScoreBuffer::m_scores = nullptr; // Array of scores
const char *ScoreBuffer::m_path = "scores.dat";

void ScoreBuffer::load()
{
	std::fstream fin;
	fin.open(m_path, std::ios_base::binary | std::ios_base::in);
	if (fin.is_open())
	{
		fin >> m_nScores;
		m_scores = new ScoreData[m_nScores];
		fin.read((char*)m_scores, sizeof(ScoreData)*m_nScores);
	}
	fin.close();
}
//void ScoreBuffer::drawGame(int x, int y)
//{
//	char c_score[1];
//	DrawString(c_score, 700, 100);
//}
void ScoreBuffer::draw(int x, int y)
{
	sort();
	for (int i = 0; i < 10 && i < m_nScores; ++i)
	{
		char c_score[8];	

		itoa(m_scores[i], c_score, 10);		
		DrawString(c_score, x , y - i * 40);
		DrawString("[C]lear HighScores", 800, 100);
		if (IsKeyDown('C')){ m_nScores = 0; }
	}
}

void ScoreBuffer::save()
{
	std::fstream fout;
	fout.open(m_path, std::ios_base::binary | std::ios_base::out);
	if (fout.is_open())
	{
		fout << m_nScores;
		fout.write((char*)m_scores, sizeof(ScoreData)*m_nScores);
		delete[] m_scores;
		m_scores = nullptr;
	}
	fout.close();
}
void Swap(ScoreData &a, ScoreData &b)
{
	ScoreData t = a;
	a = b;
	b = t;
}

void ScoreBuffer::sort()
{
	for (int i = 0; i < m_nScores; ++i)
	{
		for (int j = 0; j < m_nScores - 1; ++j)
		{
			if (m_scores[j] < m_scores[j + 1])
			{
				Swap(m_scores[j], m_scores[j + 1]);
			}
		}
	}
}

void ScoreBuffer::addScore(ScoreData a_score)
{
	ScoreData *old_scores  = m_scores;
	m_scores = new ScoreData[m_nScores + 1];

	for (int i = 0; i < m_nScores; ++i)
		m_scores[i] = old_scores[i];

	delete[] old_scores;

	m_scores[m_nScores] = a_score;
	m_nScores++;
}