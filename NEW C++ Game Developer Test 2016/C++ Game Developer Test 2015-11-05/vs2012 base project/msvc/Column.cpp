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
	uniform_int_distribution<int> rand(0, 4);

	for (int i = 0; i < size; i++)
	{
		slots.push_back(*new Slot(bottomPosX, bottomPosY - 42.0f * (i + 1)));
		gems.push_back(*new Gem(rand(eng), slots.at(i).getX(), slots.at(i).getY()));
		slots.at(i).setGem(gems.at(i));
	}
}

void Column::display(King::Engine& engine)
{
	for (int i = 0; i < gems.size() && &gems.at(i) != NULL; i++)
	{
			gems.at(i).display(engine);

			if (gems.at(i).isMouseClicked(engine))
			{
				deleteGem(i);
			}
		
	}
}

void Column::update(King::Engine& engine)
{

}

int Column::getSize()
{
	return gems.size();
}


void Column::deleteGem(int i)
{
	gems.erase(gems.begin() + i);
	slots.at(i).deleteGem();
}

Gem Column::getGem(int i)
{
	return gems.at(i);
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
	
	for (int i = 0; i < slots.size() - 1; i++)
	{
		if (slots.at(i).isEmpty())
		{
			if (!slots.at(i + 1).isEmpty())
			{
				gems.at(i + 1).fall();

				if (gems.at(i + 1).getY() >= slots.at(i + 1).getY())
				{
					slots.at(i).setGem(gems.at(i + 1));
					slots.at(i + 1).deleteGem();
				}
			}
		}
	}
	
}


