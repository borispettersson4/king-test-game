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
		slots.push_back(*new Slot(bottomPosX, bottomPosY - 42.0f * (i + 1)));
		spawnGem(i);
		printf("Gem in %d is type : %d \n", i, slots.at(i).getGem().getGemType());
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
	if (slots.at(7).isEmpty()) 
	{
		spawnGem(7);
		//canDelete = true;
	}

	slideDown();
	filterGems();
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

void Column::slideDown()
{
	
	for (int i = 0; i < slots.size(); i++)
	{
		if (slots.at(i).isEmpty())
		{
			try
			{
				if (!slots.at(i + 1).isEmpty()) 
				{
					if (gems.at(i).getY() < slots.at(i).getY())
					{
						gems.at(i).fall();
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
					if (gems.at(i).getY() < slots.at(i).getY())
					{
						gems.at(i).fall();
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
					if (gems.at(i).getY() < slots.at(i).getY())
					{
						gems.at(i).fall();
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
			catch (exception e)
			{
			}
		}


	}
	
}

void Column::filterGems() 
{
	if (canDelete)
		for (int i = 0; i < gems.size() - 2 && &gems.at(i + 1) != NULL; i++)
		{
			if (gems.at(i).getGemType() == gems.at(i + 1).getGemType() && gems.at(i).getGemType() == gems.at(i + 2).getGemType())
			{
				canDelete = false;
				gems.at(i).markForDeletion();
				gems.at(i + 1).markForDeletion();
				gems.at(i + 2).markForDeletion();
			}
		}

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


