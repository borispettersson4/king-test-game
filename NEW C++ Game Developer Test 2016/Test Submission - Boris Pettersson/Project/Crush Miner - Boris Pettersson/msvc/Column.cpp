#include "Column.h"

Column::Column()
{
	bottomXPos = 0;
	bottomYPos = 0;

	setSize(0);
	canDelete = true;
	speed = 1;
}

Column::~Column()
{
}

Column::Column(float bottomX, float bottomY, int size)
{
	bottomXPos = bottomX;
	bottomYPos = bottomY;

	setSize(size);
	canDelete = true;
	speed = 1;
}

vector<Gem> & Column::getGems() 
{
	return gems;
}

vector<Slot> & Column::getSlots()
{
	return slots;
}

void Column::spawnGem(int i) 
{
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> rand(0, 4);

	try
	{
		if (gems.size() < 8)
		{
			gems.push_back(*new Gem(rand(eng), slots.at(i).getX(), slots.at(i).getY()));
			slots.at(i).setGem(gems.at(i));
		}
	}
	catch (exception e) {}
}

void Column::setSize(int size)
{
	for (int i = 0; i < size; i++)
	{
		slots.push_back(*new Slot(bottomXPos, bottomYPos - 42.0f * (i + 1)));
		spawnGem(i);
	}
}

void Column::setSpeed(float s) 
{
	speed = s;
}

void Column::display(King::Engine& engine)
{
	for (int i = 0; i < gems.size() && &gems.at(i) != NULL; i++)
	{
			gems.at(i).display(engine);
	}
}

void Column::update(King::Engine& engine)
{
	if (isFull()) 
	{
		manageDeletedGems();
	}
	else
	{
		slideDown();
	}
}

float Column::getSpeed() 
{
	return speed;
}

int Column::getSize()
{
	return gems.size();
}

void Column::deleteGem(int i)
{
	if(&gems.at(i) != NULL)
	gems.erase(gems.begin() + i);
	slots.at(i).deleteGem();
}

Gem & Column::getGem(int i)
{
	return gems.at(i);
}

Slot & Column::getSlot(int i)
{
	return slots.at(i);
}

bool Column::isFull() {

	for (int i = 0; i < slots.size(); i++)
	{
		if (slots[i].isEmpty())
		{
			return false;
		}
	}
	return true;
}

bool Column::isDeleting() {

	for (int i = 0; i < gems.size(); i++)
	{
		if (gems.at(i).isMarkedForDeletion())
		{
			return true;
		}
	}
	return false;
}

bool Column::isDeleteReady() 
{
	return canDelete;
}

void Column::slideDown()
{
	if (slots.at(slots.size() - 1).isEmpty())
	{
		spawnGem(slots.size() - 1);
	}
	
	for (int i = 0; i < slots.size(); i++)
	{
		if (slots.at(i).isEmpty())
		{
				if (!slots.at(i + 1).isEmpty()) 
				{
					if (gems.at(i).getY() < slots.at(i).getY() + 5.0f)
					{
						gems.at(i).moveDown(10*speed);
					}
					else
					{
						slots.at(i).setGem(gems.at(i));
						slots.at(i + 1).deleteGem();
						gems.at(i).setY(slots.at(i).getY());
						gems.at(i).setX(slots.at(i).getX());
						canDelete = true;
						break;
					}
				}
			}
		}
}

void Column::manageDeletedGems() 
{
	for (int i = 0; i < gems.size() && &gems.at(i) != NULL; i++)
	{
		if (isFull())
		{
			if (gems.at(i).isMarkedForDeletion())
			{
				deleteGem(i);
			}
		}
	}
}

void Column::setDeleteStatus(bool status) 
{
	canDelete = status;
}

void Column::markForDeletion(int i) 
{
	gems.at(i).markForDeletion(true);
}

void Column::selectGem(int i, bool status) 
{
	gems.at(i).select(status);
}

bool Column::isMouseClicked(int i, King::Engine& engine) 
{
	return getSlot(i).isMouseClicked(engine);
}



