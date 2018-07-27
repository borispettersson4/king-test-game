#include <king/Engine.h>
#include <king/Updater.h>
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


};

