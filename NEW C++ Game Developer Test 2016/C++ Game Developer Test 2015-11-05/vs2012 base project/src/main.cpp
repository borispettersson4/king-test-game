#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>
#include "c:\Users\Boris\Desktop\Development\king-test-game\NEW C++ Game Developer Test 2016\C++ Game Developer Test 2015-11-05\vs2012 base project\msvc\Gem.h"
#include  "c:\Users\Boris\Desktop\Development\king-test-game\NEW C++ Game Developer Test 2016\C++ Game Developer Test 2015-11-05\vs2012 base project\msvc\Column.h"
//**********************************************************************

class CrushGame : public King::Updater {
private:
	King::Engine mEngine;
	float mRotation;
	float mCurrentDiamondX;
	float mCurrentDiamondY;
	//Gem g =  * new Gem(2, 100.0f, 100.0f);
	//Gem h = *new Gem(4, 150.0f, 150.0f);
	Column col = *new Column(325,440,8);
	

public:

	CrushGame()
		: mEngine("./assets")
		, mRotation(0.0f) {
	}

	void Start() {
	//	g.move(100.0f, 100.0f);
	//	g.setType(0);
		mEngine.Start(*this);
	}

	void Update() {

		mEngine.Render(King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f);
		
		//g.display(mEngine);
		//h.display(mEngine);
		col.display(mEngine);
		col.slideDown();
		col.update(mEngine);

		//col.slideDown();
		//g.fall();

		//mEngine.Render(King::Engine::TEXTURE_GREEN, 650.0f, 100.0f);
		//mEngine.Render(King::Engine::TEXTURE_RED, 100.0f, 450.0f);
		//mEngine.Render(King::Engine::TEXTURE_BLUE, 650.0f, 450.0f);

		//mEngine.Write("Green", 650.0f, 140.0f);
		//mEngine.Write("Red", 100.0f, 490.0f);
		//mEngine.Write("Blue", 650.0f, 490.0f);
		//printf("* Debug: %d \n", col.getSize());
		const char s[] = "";
		mRotation += mEngine.GetLastFrameSeconds();
		mEngine.Write(s, mEngine.GetWidth() / 2.0f, mEngine.GetHeight() / 2.0f, 0);

		if (mEngine.GetMouseButtonDown()) {

			//if(h.isMouseHovered(mEngine))
			//h.move(mEngine.GetMouseX(), mEngine.GetMouseY());

			//if (g.isMouseHovered(mEngine))
				//g.move(mEngine.GetMouseX(), mEngine.GetMouseY());

			//mYellowDiamondX = mEngine.GetMouseX();
			//mYellowDiamondY = mEngine.GetMouseY();
			//mye
		}
		//mEngine.Render(King::Engine::TEXTURE_YELLOW, mYellowDiamondX, mYellowDiamondY);
		//mEngine.Write("Click to", mYellowDiamondX, mYellowDiamondY + 40.0f);
		//mEngine.Write("move me!", mYellowDiamondX, mYellowDiamondY + 70.0f);
	}
};

//**********************************************************************

int main(int argc, char *argv[]) {
	CrushGame game;
	game.Start();

	return 0;
}


