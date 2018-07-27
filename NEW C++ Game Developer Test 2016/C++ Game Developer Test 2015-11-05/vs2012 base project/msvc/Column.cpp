#include "Column.h"

Column::Column()
{

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

}

vector<Gem> Column::getGems() 
{
	return gems;
}

vector<Slot> Column::getSlots()
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
		//printf("Gem in %d is type : %d \n", i, slots.at(i).getGem().getGemType());
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
				gems.at(i).markForDeletion();
				//gems.at(i).select(true);
			}
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
	display(engine);

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

Gem Column::getGem(int i)
{
	return gems.at(i);
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
	
	for (int i = 0; i < slots.size() - 1; i++)
	{
		if (slots.at(i).isEmpty())
		{
				if (!slots.at(i + 1).isEmpty()) 
				{
					if (gems.at(i).getY() < slots.at(i).getY() + 5.0f)
					{
						gems.at(i).moveDown();
					}
					else
					{
						slots.at(i).setGem(gems.at(i));
						slots.at(i + 1).deleteGem();
						gems.at(i).setY(gems.at(i).getY() - 10.0f);
						gems.at(i).setX(slots.at(i).getX());
						canDelete = true;
						//printf("REMOVED A GEM \n");
					}
				}
				else if (!slots.at(i + 2).isEmpty())
				{
					if (gems.at(i).getY() < slots.at(i).getY() + 5.0f)
					{
						gems.at(i).moveDown();
					}
					else
					{
						slots.at(i).setGem(gems.at(i));
						slots.at(i + 2).deleteGem();
						gems.at(i).setY(gems.at(i).getY() - 10.0f);
						gems.at(i).setX(slots.at(i).getX());
						canDelete = true;
						//printf("REMOVED A GEM \n");
					}
				}

				else if (!slots.at(i + 3).isEmpty())
				{
					if (gems.at(i).getY() < slots.at(i).getY() + 5.0f)
					{
						gems.at(i).moveDown();
					}
					else
					{
						slots.at(i).setGem(gems.at(i));
						slots.at(i + 3).deleteGem();
						gems.at(i).setY(gems.at(i).getY() - 10.0f);
						gems.at(i).setX(slots.at(i).getX());
						canDelete = true;
						//printf("REMOVED A GEM \n");
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
			printf("Marked Status : %d \n", gems.at(i).isMarkedForDeletion());
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
	gems.at(i).markForDeletion();
}



