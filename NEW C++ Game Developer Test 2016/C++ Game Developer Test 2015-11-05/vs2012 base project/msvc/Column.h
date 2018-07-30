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
	vector<Gem> gems;
	vector<Slot> slots;
	float topXPos;
	float topYPos;
	float bottomXPos;
	float bottomYPos;
	float speed;
	bool canDelete;

public:
	Column();
	Column(float bottomX, float bottomY, int size);
	virtual ~Column();

	vector<Gem> & getGems();
	vector<Slot> & getSlots();
	Gem & getGem(int i);
	Slot & getSlot(int i);

	void setSize(int size);
	void display(King::Engine& engine);
	void update(King::Engine& engine);
	void slideDown();
	void manageDeletedGems();
	void deleteGem(int i);
	void spawnGem(int i);
	void setDeleteStatus(bool status);
	void markForDeletion(int i);
	void selectGem(int i, bool status);
	void setSpeed(float s);

	float getSpeed();
	int getSize();

	bool isDeleteReady();
	bool isFull();
	bool isDeleting();
	bool isMouseClicked(int i, King::Engine& engine);


};

