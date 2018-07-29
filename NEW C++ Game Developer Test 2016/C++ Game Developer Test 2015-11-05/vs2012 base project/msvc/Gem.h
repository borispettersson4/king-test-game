#pragma once
#ifndef GEM_H
#define GEM_H

#include <king/Engine.h>
#include <string>
#include <chrono>

#endif

using namespace std;

class Gem
{
private:
	float xPos;
	float yPos;
	float xScale;
	float yScale;
	int gemType;

	bool moving;
	bool selected;
	bool markedForDeletion;
	bool markedForSwap;
	bool visible;
public:
	Gem();
	Gem(int type, float x, float y);
	virtual ~Gem();

	float getX();
	float getY();
	int getGemType();
	void setGemType(int i);
	void setX(float x);
	void setY(float x);
	void display(King::Engine& engine);
	void moveLeft(int amount);
	void moveRight(int amount);
	void moveUp(int amount);
	void moveDown(int amount);
	void playFlashingTexture();

	bool isMouseHovered(King::Engine& engine);
	bool isMouseClicked(King::Engine& engine);
	bool isMoving();
	void markForDeletion(bool status);
	bool isMarkedForDeletion();
	void markForSwap(bool status);
	bool isMarkedForSwap();
	void select(bool s);
	bool isSelected();
};

