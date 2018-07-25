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
	return &currentGem == NULL;
}

Gem Slot::getGem() 
{
	return currentGem;
}

Gem* Slot::getGemPointer()
{
	return &currentGem;
}

void Slot::setGem(Gem g) 
{
	currentGem = g;
}

void Slot::deleteGem() 
{
	delete &currentGem;
}

bool Slot::isMouseClicked(King::Engine& engine) 
{
	return currentGem.isMouseClicked(engine);
}
