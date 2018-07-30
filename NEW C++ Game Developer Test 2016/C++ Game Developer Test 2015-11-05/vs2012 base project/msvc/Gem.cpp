#include "Gem.h"

Gem::Gem()
{
	xPos = 0;
	yPos = 0;
	gemType = 0;

	markedForDeletion = false;
	markedForSwap = false;
	moving = false;
	selected = false;
	visible = true;
}

Gem::Gem(int type, float x, float y)
{
	xPos = x;
	yPos = y;
	gemType = type;

	markedForDeletion = false;
	markedForSwap = false;
	moving = false;
	selected = false;
	visible = true;
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

float Gem::getXScale()
{
	return xScale;
}

float Gem::getYScale()
{
	return yScale;
}

void Gem::setX(float x) 
{
	xPos = x;
}

void Gem::setY(float y)
{
	yPos = y;
}

void Gem::display(King::Engine& engine)
{
		switch (gemType)
		{
		case 0:
			if(visible)
			engine.Render(King::Engine::TEXTURE_BLUE, xPos, yPos);
			break;

		case 1:
			if (visible)
			engine.Render(King::Engine::TEXTURE_GREEN, xPos, yPos);
			break;

		case 2:
			if (visible)
			engine.Render(King::Engine::TEXTURE_PURPLE, xPos, yPos);
			break;

		case 3:
			if (visible)
			engine.Render(King::Engine::TEXTURE_RED, xPos, yPos);
			break;

		case 4:
			if (visible)
			engine.Render(King::Engine::TEXTURE_YELLOW, xPos, yPos);
			break;
		}

		xScale = engine.GetTextureWidth(engine.TEXTURE_YELLOW);
		yScale = engine.GetTextureHeight(engine.TEXTURE_YELLOW);

	if(selected)
	{
		playFlashingTexture();
	}
	else
	{
		visible = true;
	}
}

void Gem::playFlashingTexture() 
{
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>
	(
		chrono::system_clock::now().time_since_epoch() / 200
	);
	
	if(ms.count() %  2 == 0)
		visible = false;
		else
		visible = true;

}

void Gem::moveLeft(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		xPos--;
		moving = true;
	}
	moving = false;
}

void Gem::moveRight(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		xPos++;
		moving = true;
	}
	moving = false;
}

void Gem::moveUp(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		yPos--;
		moving = true;
	}
	moving = false;
}

void Gem::moveDown(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		yPos++;
		moving = true;
	}
	moving = false;
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

bool Gem::isMoving() 
{
	return moving;
}

void Gem::markForDeletion(bool status) 
{
	markedForDeletion = status;
}

bool Gem::isMarkedForDeletion() 
{
	return 	markedForDeletion;
}

void Gem::markForSwap(bool status)
{
	markedForSwap = status;
}

bool Gem::isMarkedForSwap()
{
	return 	markedForSwap;
}

bool Gem::isSelected() 
{
	return selected;
}

void Gem::select(bool s) 
{
	selected = s;
}
