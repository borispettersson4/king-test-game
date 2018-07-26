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

	canDelete = true;

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

			if (gems.at(i).isMouseClicked(engine) && canDelete)
			{
				canDelete = false;
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
	for (int i = 0; i < slots.size(); i++)
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
	
	for (int i = 0; i < slots.size(); i++)
	{
		if (slots.at(i).isEmpty())
		{
			try
			{
				if (!slots.at(i + 1).isEmpty() && gems.at(i).getY() < slots.at(i).getY())
				{
					gems.at(i).fall();
				}
				else 
				{
					slots.at(i).setGem(gems.at(i));
					slots.at(i + 1).deleteGem();
					gems.at(i).setY(gems.at(i).getY() - 7.5f);
					gems.at(i).setX(slots.at(i).getX());
					canDelete = true;
				}
			}
			catch (exception e)
			{
			}
		}


	}
	
}


