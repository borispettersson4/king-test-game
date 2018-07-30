#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>
#include <c:\Users\Boris\Desktop\Development\king-test-game\NEW C++ Game Developer Test 2016\C++ Game Developer Test 2015-11-05\vs2012 base project\msvc\Grid.h>

int gameStage = 0;

//**********************************************************************

class CrushMiner : public King::Updater {
private:
	King::Engine mEngine;
	float mRotation;
	float mCurrentDiamondX;
	float mCurrentDiamondY;

	Grid grid;

	clock_t startTime;
	int timeLimit = 60;

public:

	CrushMiner()
		: mEngine("./assets")
		, mRotation(0.0f) {
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
				gameStage = 1;
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

		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);
		grid.update(mEngine);
		grid.display(mEngine);
		mEngine.Write(timeChar, 100, 450, 0);

		string scoreString = to_string(grid.getScore());
		const char * scoreChar = scoreString.c_str();

		mEngine.Write("SCORE", 90, 100, 0);
		mEngine.Write(scoreChar, 90, 140, 0);

		if (time <= 0) 
		{
			gameStage = 2;
		}
	}

	void playOutro() 
	{
		chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>
		(
			chrono::system_clock::now().time_since_epoch() / 300
		);

		if (ms.count() % 2 != 0)
			mEngine.Write("click to restart game", 255, 500, 0);

		mEngine.Write("GAME OVER", 305, 150, 0);

		string scoreString = to_string(grid.getScore());
		const char * scoreChar = scoreString.c_str();

		mEngine.Write("Your Score :", 250, 250, 0);
		mEngine.Write(scoreChar, 450, 250, 0);

		if (mEngine.GetMouseButtonDown())
		{
			gameStage = 0;
			grid = *new Grid(330, 440, 8);
		}
	}

	void Start() 
	{
		grid = *new Grid(330, 440, 8);
		mEngine.Start(*this);
	}

	void Update() 
	{
		switch (gameStage)
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
};

//**********************************************************************

int main(int argc, char *argv[])
{
	CrushMiner game;
	game.Start();

	return 0;
}


