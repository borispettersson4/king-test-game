#include "Column.h"

Column::Column()
{

}

Column::~Column()
{
}

Column::Column(float bottomX, float bottomY, int size) 
{
	bottomPosX = bottomX;
	bottomPosY = bottomY;

	setSize(size);

}

void Column::setSize(int size)
{
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> rand(0,4);

	for (int i = 0; i < size; i++)
	{
		slots.push_back(*new Slot(bottomPosX, bottomPosY - 42.0f * (i + 1)));
		slots.at(i).setGem(*new Gem(rand(eng), slots.at(i).getX(), slots.at(i).getY()));
	}
}

void Column::display(King::Engine& engine)
{
	for (int i = 0; i < slots.size(); i++)
	{
		if (!slots.at(i).isEmpty())
		{
			slots.at(i).getGem().display(engine);
		}
	}
}

void Column::update(King::Engine& engine)
{
	if (slots.at(1).getGem().isMouseClicked(engine))
	{
		slots.at(1).deleteGem();
	}
}

int Column::getSize() 
{
	return slots.size();
}

string Column::toString() 
{
	return "" + slots.max_size();
}

bool Column::isFull() {
	
	bool full = true;
	for (int i = 0; i < SIZE; i++)
	{
		if (slots[i].isEmpty()) 
		{
			full = false;
			break;
		}

	}
	return full;
}

void Column::slideDown() 
{
	for (int i = 0; i < SIZE; i++)
	{
		if (slots[i].isEmpty()) 
		{
			if (!slots[i + 1].isEmpty())
			{
				slots[i + 1].getGem().fall();

				if (slots[i + 1].getGem().getY() >= slots[i].getY()) 
				{
					slots[i].setGem(*new Gem(slots[i + 1].getGem()));
					slots[i + 1].deleteGem();
				}
			}
		}
	}
}


