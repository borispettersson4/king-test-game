#include "Gem.h"

Gem::Gem()
{
	xPos = 0;
	yPos = 0;
	gemType = 0;
}

Gem::Gem(int type, float x, float y)
{
	xPos = x;
	yPos = y;
	gemType = type;
}

void Gem::setGemType(int i)
{
	gemType = i;
}

int Gem::getGemType()
{
	return gemType;
}

Gem::~Gem()
{
}

float Gem::getX() 
{
	return xPos;
}

float Gem::getY()
{
	return yPos;
}

void Gem::move(float x, float y)
{
	xPos = x - xScale/2;
	yPos = y - yScale / 2;
}

void Gem::setX(float x) 
{
	xPos = x;
}

void Gem::setY(float y)
{
	xPos = y;
}

void Gem::display(King::Engine& engine)
{
	switch (gemType)
	{
	case 0:
		engine.Render(King::Engine::TEXTURE_BLUE, xPos, yPos);
		xScale = engine.GetTextureWidth(engine.TEXTURE_BLUE);
		yScale = engine.GetTextureHeight(engine.TEXTURE_BLUE);
		break;

	case 1:
		engine.Render(King::Engine::TEXTURE_GREEN, xPos, yPos);
		xScale = engine.GetTextureWidth(engine.TEXTURE_GREEN);
		yScale = engine.GetTextureHeight(engine.TEXTURE_GREEN);
		break;

	case 2:
		engine.Render(King::Engine::TEXTURE_PURPLE, xPos, yPos);
		xScale = engine.GetTextureWidth(engine.TEXTURE_PURPLE);
		yScale = engine.GetTextureHeight(engine.TEXTURE_PURPLE);
		break;

	case 3:
		engine.Render(King::Engine::TEXTURE_RED, xPos, yPos);
		xScale = engine.GetTextureWidth(engine.TEXTURE_RED);
		yScale = engine.GetTextureHeight(engine.TEXTURE_RED);
		break;

	case 4:
		engine.Render(King::Engine::TEXTURE_YELLOW, xPos, yPos);
		xScale = engine.GetTextureWidth(engine.TEXTURE_YELLOW);
		yScale = engine.GetTextureHeight(engine.TEXTURE_YELLOW);
		break;
	}

}

void Gem::fall() 
{
	for(int i = 0; i < 10; i++)
	yPos++;
}

bool Gem::isMouseHovered(King::Engine& engine) 
{
	return(engine.GetMouseX() >= xPos && engine.GetMouseX() <= (xScale + xPos)
		&& engine.GetMouseY() >= yPos && engine.GetMouseY() <= (yScale + yPos)
		);
}

bool Gem::isMouseClicked(King::Engine& engine)
{
	return (engine.GetMouseButtonDown() && isMouseHovered(engine));
}
