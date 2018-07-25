#include "Gem.h"
#pragma once
class Slot
{
private:
	float xPos;
	float yPos;
	Gem currentGem;
public:
	Slot();
	Slot(float x, float y);
	virtual ~Slot();
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	bool isEmpty();
	Gem getGem();
	Gem* getGemPointer();
	void setGem(Gem g);
	void deleteGem();
	bool isMouseClicked(King::Engine& engine);
};

