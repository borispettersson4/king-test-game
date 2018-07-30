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

void Grid::setX(float x) 
{
	xPos = x;
}

void Grid::setY(float y)
{
	yPos = y;
}

void Grid::setSize(int size)
{
	for (int i = 0; i < size; i++)
	{
		columns.push_back(*new Column(xPos + 42*(i), yPos, size));
	}
}

void Grid::setSpeed(float s) 
{
	for (int i = 0; i < columns.size(); i++)
	{
		columns.at(i).setSpeed(s);
	}
}

void Grid::setScore(int s)
{
	score = s;
}

int Grid::getScore() 
{
	return score;
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
		findMatchingGems();
		manageSelection(engine);
	}
}

void Grid::display(King::Engine &engine) 
{
	for (int i = 0; i < columns.size(); i++)
	{
		columns.at(i).display(engine);
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
					filterGemSelection(i,j, columns.at(i).getGem(j));
				}

				else if (i > 0 && columns.at(i - 1).getGem(j).isSelected())
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
						gemA.markForSwap(false);
						gemB.markForSwap(false);

						int tempGemType = gemA.getGemType();
						gemA.setGemType(gemB.getGemType());
						gemB.setGemType(tempGemType);

						gemA.setX(slotA.getX());
						gemA.setY(slotA.getY());
						gemB.setX(slotB.getX());
						gemB.setY(slotB.getY());

						if (timesSwapped % 2 == 0)
						{
							if (!findMatchingGems())
							{
								timesSwapped++;
								swap(slotB, slotA, gemB, gemA);
							}
						}
						else
						{
							timesSwapped++;
						}
					}
			}
}

void Grid::clearSelection() 
{
	for (int i = 0; i < columns.size(); i++)
	{
		for (int j = 0; j < columns.at(i).getGems().size(); j++)
		{
			columns.at(i).getGem(j).select(false);
		}
	}
}

void Grid::filterGemSelection(int i, int j, Gem &currentGem) 
{
	static Gem* gemA = NULL;
	static Gem* gemB = NULL;

	if (gemA == NULL && !currentGem.isMarkedForSwap())
	{
		gemA = &currentGem;
		gemA->select(true);
	}
	else if (gemB == NULL && !currentGem.isMarkedForSwap())
	{
		gemB = &currentGem;
		gemB->select(true);
	}

	else if (&currentGem == gemA || &currentGem == gemB)
	{
		currentGem.select(true);
	}

	else if (gemA != NULL && gemB != NULL && !gemA->isMarkedForSwap() && !gemB->isMarkedForSwap())
	{
		gemA->select(false);
		gemA = &currentGem;
		gemA->select(true);
		gemB->select(false);
		gemB = NULL;
	}
}

bool Grid::isMultipleSelected(int gemCount)
{
	int selectedGems = 0;

	for (int i = 0; i < columns.size(); i++)
	{
		for (int j = 0; j < columns.at(i).getGems().size(); j++)
		{
			if (columns.at(i).getGem(j).isSelected())
			{
				selectedGems++;
			}
		}
	}

	return (selectedGems >= gemCount);
}

bool Grid::findMatchingGems()
{
	bool foundMatch = false;

	for (int j = 0; j < columns.size(); j++)
	{
		for (int i = 0; i < columns.at(j).getGems().size() - 2 && &columns.at(j).getGems().at(i + 1) != NULL; i++)
		{
			if (columns.at(j).getGems().at(i).getGemType() == columns.at(j).getGems().at(i + 1).getGemType() &&
				columns.at(j).getGems().at(i).getGemType() == columns.at(j).getGems().at(i + 2).getGemType())
			{
				columns.at(j).setDeleteStatus(false);
				columns.at(j).markForDeletion(i);

				if (columns.at(j).getGem(i + 1).getGemType() == columns.at(j).getGem(i).getGemType())
					columns.at(j).markForDeletion(i + 1);

				if (columns.at(j).getGem(i + 2).getGemType() == columns.at(j).getGem(i).getGemType())
					columns.at(j).markForDeletion(i + 2);

				score += 30;
				foundMatch = true;
				break;
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

					if (columns.at(j + 1).getGem(i).getGemType() == columns.at(j).getGem(i).getGemType())
						columns.at(j + 1).markForDeletion(i);
					if (columns.at(j + 2).getGem(i).getGemType() == columns.at(j).getGem(i).getGemType())
						columns.at(j + 2).markForDeletion(i);

					score += 30;
					foundMatch = true;
					break;
				}
		}
	}

	return foundMatch;
}

bool Grid::isFull() 
{
	for (int i = 0; i < columns.size(); i++) 
	{
		if (!columns.at(i).isFull())
			return false;
	}
	return true;
}

bool Grid::isDeleting()
{
	for (int i = 0; i < columns.size(); i++)
	{
		if (columns.at(i).isDeleting())
			return true;
	}
	return false;
}
