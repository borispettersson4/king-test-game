#pragma once
#ifndef GEM_H
#define GEM_H

#include <string>
#include <king/Engine.h>

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

	bool falling;
	bool selected;
	bool isMarkedForDel;
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
	void move(float x, float y);
	void display(King::Engine& engine);
	void fall();
	bool isMouseHovered(King::Engine& engine);
	bool isMouseClicked(King::Engine& engine);
	bool isFalling();
	void markForDeletion();
	bool isMarkedForDeletion();
	void select(bool s);
	bool isSelected();
};

