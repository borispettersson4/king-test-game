#include <list>
#include <random>
#include "Gem.h"
#include "Slot.h"

using namespace std;

#pragma once
class Column
{
protected:
	static const int SIZE = 8;
	vector<Gem> gems;
	vector<Slot> slots;
	float topPosX;
	float topPosY;
	float bottomPosX;
	float bottomPosY;
	float yScale;

public:
	Column();
	Column(float bottomX, float bottomY, int size);
	virtual ~Column();
	void setSize(int size);
	void display(King::Engine& engine);
	void update(King::Engine& engine);
	void slideDown();
	bool isFull();
	int getSize();
	string toString();
	Gem getGem(int i);
	void deleteGem(int i);


};

