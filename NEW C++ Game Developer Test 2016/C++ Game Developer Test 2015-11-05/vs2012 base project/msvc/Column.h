#include <king/Engine.h>
#include <king/Updater.h>
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
	float topXPos;
	float topYPos;
	float bottomXPos;
	float bottomYPos;
	float yScale;
	bool canDelete;

public:
	Column();
	Column(float bottomX, float bottomY, int size);
	virtual ~Column();
	vector<Gem> getGems();
	vector<Slot> getSlots();
	void setSize(int size);
	void display(King::Engine& engine);
	void update(King::Engine& engine);
	void slideDown();
	void manageDeletedGems();
	bool isFull();
	int getSize();
	string toString();
	Gem getGem(int i);
	void deleteGem(int i);
	void spawnGem(int i);
	bool isDeleteReady();
	void setDeleteStatus(bool status);
	void markForDeletion(int i);

};

