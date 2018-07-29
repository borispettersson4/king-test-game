#include "Grid.h"

Grid::Grid()
{
	xPos = 0;
	yPos = 0;
	setSize(0);
}

Grid::~Grid()
{
}

Grid::Grid(float x, float y, int size)
{
	xPos = x;
	yPos = y;
	setSize(size);
}

void Grid::setSize(int size)
{
	for (int i = 0; i < size; i++)
	{
		columns.push_back(*new Column(xPos + 42*(i), yPos, size));
	}
}

int Grid::getSize() 
{
	return columns.size();
}

void Grid::update(King::Engine& engine) 
{
	for (int i = 0; i < columns.size(); i++)
	{
		columns.at(i).update(engine);
	}
	if (isFull())
	{
		manageSelection(engine);
		filterGems();
	}

}

void Grid::filterGems() 
{
	for (int j = 0; j < columns.size(); j++)
	{
			for (int i = 0; i < columns.at(j).getGems().size() - 2 && &columns.at(j).getGems().at(i + 1) != NULL; i++)
			{
				if (columns.at(j).getGems().at(i).getGemType() == columns.at(j).getGems().at(i + 1).getGemType() &&
					columns.at(j).getGems().at(i).getGemType() == columns.at(j).getGems().at(i + 2).getGemType())
				{
					columns.at(j).setDeleteStatus(false);
					columns.at(j).markForDeletion(i);
					columns.at(j).markForDeletion(i + 1);
					columns.at(j).markForDeletion(i + 2);
				}
			}
			for (int i = 0; i < columns.at(j).getGems().size(); i++)
			{
				if (j < columns.size() - 2 && isFull())
					if (columns.at(j).getGems().at(i).getGemType() == columns.at(j + 1).getGems().at(i).getGemType() &&
						columns.at(j).getGems().at(i).getGemType() == columns.at(j + 2).getGems().at(i).getGemType())
					{
							columns.at(j).setDeleteStatus(false);
							columns.at(j).markForDeletion(i);
							columns.at(j + 1).markForDeletion(i);
							columns.at(j + 2).markForDeletion(i);
					}
			}
			
		
	}

}

void Grid::manageSelection(King::Engine& engine) 
{
	for (int i = 0; i < columns.size(); i++)
	{
		for (int j = 0; j < columns.at(i).getGems().size(); j++)
		{
			if (columns.at(i).getGem(j).isMouseClicked(engine) || columns.at(i).getGem(j).isMarkedForSwap())
			{
				if ((i == 0 || !columns.at(i - 1).getGem(j).isSelected()) && 
					(i == columns.size() - 1 || !columns.at(i + 1).getGem(j).isSelected()) &&
					(j == 0 || !columns.at(i).getGem(j - 1).isSelected()) &&
					(j == columns.at(i).getGems().size() - 1 || !columns.at(i).getGem(j + 1).isSelected()))
				{
					columns.at(i).selectGem(j, true);
				}

				else if(i > 0 && columns.at(i - 1).getGem(j).isSelected())
				{
					swap(columns.at(i - 1).getSlot(j), columns.at(i).getSlot(j), 
						 columns.at(i - 1).getGem(j), columns.at(i).getGem(j));
				}

				else if (i < columns.size() - 1 && columns.at(i + 1).getGem(j).isSelected())
				{
					swap(columns.at(i + 1).getSlot(j), columns.at(i).getSlot(j),
						 columns.at(i + 1).getGem(j), columns.at(i).getGem(j));
				}

				else if (j > 0 && columns.at(i).getGem(j - 1).isSelected())
				{
					swap(columns.at(i).getSlot(j - 1), columns.at(i).getSlot(j),
						 columns.at(i).getGem(j - 1), columns.at(i).getGem(j));
				}

				else if (j < columns.at(i).getGems().size() - 1 && columns.at(i).getGem(j + 1).isSelected())
				{
					swap(columns.at(i).getSlot(j + 1), columns.at(i).getSlot(j),
						columns.at(i).getGem(j + 1), columns.at(i).getGem(j));
				}
			}
		}
	}
}

void Grid::swap(Slot &slotA, Slot &slotB, Gem &gemA, Gem &gemB)
{
	gemA.markForSwap(true);
	gemB.markForSwap(true);
	static int timesSwapped = 0;

			if (!slotA.isEmpty() && !slotB.isEmpty())
			{
					if (slotA.getX() < gemB.getX() && gemA.getX() < slotB.getX())
					{
						gemB.moveLeft(2);
						gemA.moveRight(2);
					}
					else if (slotA.getX() > gemB.getX() && gemA.getX() > slotB.getX())
					{
						gemB.moveRight(2);
						gemA.moveLeft(2);
					}
					else if (slotA.getY() < gemB.getY() && gemA.getY() < slotB.getY())
					{
						gemB.moveUp(2);
						gemA.moveDown(2);
					}
					else if (slotA.getY() > gemB.getY() && gemA.getY() > slotB.getY())
					{
						gemB.moveDown(2);
						gemA.moveUp(2);
					}
					else
					{
						gemA.select(false);
						gemB.select(false);

						int tempGemType = gemA.getGemType();
						gemA.setGemType(gemB.getGemType());
						gemB.setGemType(tempGemType);

						gemA.setX(slotA.getX());
						gemA.setY(slotA.getY());
						gemB.setX(slotB.getX());
						gemB.setY(slotB.getY());

						if (timesSwapped % 2 == 0)
						{
							timesSwapped++;
							this_thread::sleep_for(chrono::milliseconds(100));
							swap(slotB,slotA,gemB,gemA);
							printf("1 \n");
						}
						else
						{
							gemA.markForSwap(false);
							gemB.markForSwap(false);
							timesSwapped++;
							printf("2 \n");
						}
					}
					if (!gemA.isMarkedForSwap() && !gemA.isMarkedForSwap())
					{
						printf("3 \n");
					}
			}

}

bool Grid::isFull() 
{
	bool temp = true;
	for (int i = 0; i < columns.size(); i++) 
	{
		if (!columns.at(i).isFull())
			temp = false;
	}
	return temp;
}