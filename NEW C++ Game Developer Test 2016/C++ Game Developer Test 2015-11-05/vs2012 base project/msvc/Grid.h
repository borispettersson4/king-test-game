#include <king/Engine.h>
#include <king/Updater.h>
#include <thread>
#include "Column.h"

#pragma once
class Grid
{
private:
	vector<Column> columns;
	int xPos;
	int yPos;
public:
	Grid();
	Grid(float x, float y, int size);
	virtual ~Grid(); 
	void setSize(int size);
	int getSize();
	void update(King::Engine& engine);
	void filterGems();
	void swap(Slot &slotA, Slot &slotB, Gem &gemA, Gem &gemB);
	void manageSelection(King::Engine& engine);
	bool isFull();


};

