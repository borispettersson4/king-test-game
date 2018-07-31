#include "Slot.h"

Slot::Slot()
{
	xPos = 0;
	yPos = 0;
}

Slot::Slot(float x, float y) 
{
	xPos = x;
	yPos = y;
}

Slot::~Slot()
{
}

float Slot::getX() 
{
	return xPos;
}

float Slot::getY()
{
	return yPos;
}

void Slot::setX(float x) 
{
	xPos = x;
}

void Slot::setY(float y)
{
	yPos = y;
}

bool Slot::isEmpty() 
{
	return currentGemPtr == NULL;
}

Gem & Slot::getGem() 
{
	return currentGem;
}

Gem* Slot::getGemPointer()
{
	return currentGemPtr;
}

void Slot::setGem(Gem &g) 
{
	currentGem = g;
	currentGemPtr = &currentGem;
}

void Slot::deleteGem() 
{
	currentGemPtr = nullptr;
}

void Slot::selectGem(bool status) 
{
	getGem().select(status);
}

bool Slot::isMouseClicked(King::Engine& engine)
{
	return getGem().isMouseClicked(engine);
}
