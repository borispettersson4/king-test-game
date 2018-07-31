#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>
#include "..\msvc\Grid.h"

int gameScreen = 0;
int highScore = 0;

//**********************************************************************

class CrushMiner : public King::Updater {
private:
	King::Engine mEngine;
	Grid grid;

	clock_t gameTimer;
	clock_t exitTimer;

	int gametimeLimit = 60;
	int retrytimeLimit = 2;

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
				gameTimer = clock();
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
		int time = gametimeLimit - (clock() - gameTimer) / 1000;
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
			exitTimer = clock();

			if (grid.getScore() > highScore)
			{
				highScore = grid.getScore();
			}
		}

	}

	void playOutro() 
	{
		chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>
		(
			chrono::system_clock::now().time_since_epoch() / 300
		);

		int time = retrytimeLimit - (clock() - exitTimer) / 1000;

		string scoreString = to_string(grid.getScore());
		const char * scoreChar = scoreString.c_str();

		string bestScoreString = to_string(highScore);
		const char * bestScoreChar = bestScoreString.c_str();

		mEngine.Write("GAME OVER", 290, 150, 0);
		mEngine.Write("Your Score :", 240, 250, 0);
		mEngine.Write(scoreChar, 475, 250, 0);
		mEngine.Write("Your Best :", 250, 350, 0);
		mEngine.Write(bestScoreChar, 475, 350, 0);

		if (time <= 0)
		{
			if (ms.count() % 2 != 0)
				mEngine.Write("click to restart game", 240, 500, 0);

			if (mEngine.GetMouseButtonDown())
			{
				gameScreen = 0;
				grid = *new Grid(330, 440, 8);
			}
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


