#include "Gem.h"
#pragma once
class Slot
{
private:
	float xPos;
	float yPos;
	Gem currentGem;
	Gem* currentGemPtr;

public:
	Slot();
	Slot(float x, float y);
	virtual ~Slot();

	Gem & getGem();
	Gem* getGemPointer();
	float getX();
	float getY();

	void setGem(Gem &g);
	void deleteGem();
	void selectGem(bool status);
	void setX(float x);
	void setY(float y);

	bool isEmpty();
	bool isMouseClicked(King::Engine& engine);
};

