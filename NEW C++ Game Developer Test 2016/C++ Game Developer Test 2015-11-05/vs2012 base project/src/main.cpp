#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>
#include "..\msvc\Grid.h"

int gameScreen = 0;
int bestScore;

//**********************************************************************

class CrushMiner : public King::Updater {
private:
	King::Engine mEngine;
	Grid grid;
	clock_t startTime;
	int timeLimit = 60;

public:
	CrushMiner()
		: mEngine("./assets") {
	}

	void Start()
	{

		grid = *new Grid(330, 440, 8);
		mEngine.Start(*this);
	}

	void Update()
	{
		switch (gameScreen)
		{
		case 0:
			playIntro();
			break;

		case 1:
			playGame();
			break;

		case 2:
			playOutro();
			break;
		}
	}

	void playIntro() 
	{
		chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>
		(
			chrono::system_clock::now().time_since_epoch() / 300
		);

		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);
		mEngine.Write("CRUSH MINER", 390, 150, 0);
		mEngine.Write("test submission by:", 10, -5, 0);
		mEngine.Write("Boris Ruiz Pettersson", 450, -5, 0);
		grid.update(mEngine);
		grid.setSpeed(1000);

		if (!grid.isDeleting() && grid.isFull()) 
		{
			if (ms.count() % 2 != 0)
				mEngine.Write("click to start", 405, 300, 0);

			if (mEngine.GetMouseButtonDown())
			{
				gameScreen = 1;
				grid.setSpeed(1);
				startTime = clock();
				grid.setScore(0);
			}
		}
		else 
		{
			mEngine.Write("loading...", 430, 300, 0);
		}
	}

	void playGame() 
	{	
		int time = timeLimit - (clock() - startTime) / 1000;
		string timeString = to_string(time);
		const char * timeChar = timeString.c_str();

		string scoreString = to_string(grid.getScore());
		const char * scoreChar = scoreString.c_str();

		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);
		grid.update(mEngine);
		grid.display(mEngine);
		mEngine.Write(timeChar, 100, 450, 0);
		mEngine.Write("SCORE", 90, 100, 0);
		mEngine.Write(scoreChar, 90, 140, 0);

		if (time <= 0) 
		{
			gameScreen = 2;
		}
	}

	void playOutro() 
	{
		chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>
		(
			chrono::system_clock::now().time_since_epoch() / 300
		);

		string scoreString = to_string(grid.getScore());
		const char * scoreChar = scoreString.c_str();
		
		string bestScoreString = to_string(grid.getScore());
		const char * bestScoreChar = bestScoreString.c_str();

		if (grid.getScore() > bestScore)
			bestScore = grid.getScore();

		mEngine.Write("GAME OVER", 305, 150, 0);
		mEngine.Write("Your Score :", 250, 250, 0);
		mEngine.Write(scoreChar, 450, 250, 0);
		mEngine.Write("Your Best :", 250, 350, 0);
		mEngine.Write(bestScoreChar, 450, 350, 0);

		if (ms.count() % 2 != 0)
			mEngine.Write("click to restart game", 255, 500, 0);

		if (mEngine.GetMouseButtonDown())
		{
			gameScreen = 0;
			grid = *new Grid(330, 440, 8);
		}
	}
};

//**********************************************************************

int main(int argc, char *argv[])
{
	CrushMiner game;
	game.Start();

	return 0;
}


