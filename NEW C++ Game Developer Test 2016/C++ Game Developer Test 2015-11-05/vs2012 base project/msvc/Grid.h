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
	int score;

	void filterGemSelection(int column, int row, Gem &currentGem);
	void swap(Slot &slotA, Slot &slotB, Gem &gemA, Gem &gemB);
	void manageSelection(King::Engine& engine);
	bool findMatchingGems();

public:
	Grid();
	Grid(float x, float y, int size);
	virtual ~Grid(); 

	int getSize();
	int getScore();

	void setX(float x);
	void setY(float y);
	void setSize(int size);
	void setSpeed(float s);
	void setScore(int s);

	void update(King::Engine& engine);
	void display(King::Engine& engine);
	void clearSelection();

	bool isMultipleSelected(int gemCount);
	bool isFull();
	bool isDeleting();

};

