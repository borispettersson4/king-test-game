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

	markedForDeletion = false;
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
			xScale = engine.GetTextureWidth(engine.TEXTURE_YELLOW);
			yScale = engine.GetTextureHeight(engine.TEXTURE_YELLOW);
			break;

		case 1:
			if (visible)
			engine.Render(King::Engine::TEXTURE_GREEN, xPos, yPos);
			xScale = engine.GetTextureWidth(engine.TEXTURE_YELLOW);
			yScale = engine.GetTextureHeight(engine.TEXTURE_YELLOW);
			break;

		case 2:
			if (visible)
			engine.Render(King::Engine::TEXTURE_PURPLE, xPos, yPos);
			xScale = engine.GetTextureWidth(engine.TEXTURE_YELLOW);
			yScale = engine.GetTextureHeight(engine.TEXTURE_YELLOW);
			break;

		case 3:
			if (visible)
			engine.Render(King::Engine::TEXTURE_RED, xPos, yPos);
			xScale = engine.GetTextureWidth(engine.TEXTURE_YELLOW);
			yScale = engine.GetTextureHeight(engine.TEXTURE_YELLOW);
			break;

		case 4:
			if (visible)
			engine.Render(King::Engine::TEXTURE_YELLOW, xPos, yPos);
			xScale = engine.GetTextureWidth(engine.TEXTURE_YELLOW);
			yScale = engine.GetTextureHeight(engine.TEXTURE_YELLOW);
			break;
		}

	if(selected)
	{
		playFlashingTexture();
	}
}

void Gem::playFlashingTexture() 
{
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>
	(
		chrono::system_clock::now().time_since_epoch() / 250
	);
	
	if(ms.count() %  2 == 0)
		visible = false;
		else
		visible = true;

}

void Gem::moveLeft()
{
	for (int i = 0; i < 10; i++)
	{
		xPos--;
		moving = true;
	}
	moving = false;
}

void Gem::moveRight()
{
	for (int i = 0; i < 10; i++)
	{
		xPos++;
		moving = true;
	}
	moving = false;
}

void Gem::moveUp()
{
	for (int i = 0; i < 10; i++)
	{
		yPos--;
		moving = true;
	}
	moving = false;
}

void Gem::moveDown() 
{
	for (int i = 0; i < 10; i++)
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

void Gem::markForDeletion() 
{
	markedForDeletion = true;
}

bool Gem::isMarkedForDeletion() 
{
	return 	markedForDeletion;
}

bool Gem::isSelected() 
{
	return selected;
}

void Gem::select(bool s) 
{
	selected = s;
}
