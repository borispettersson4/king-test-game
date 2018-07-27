#include "Grid.h"

Grid::Grid()
{
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
	for (int i = 0; i < getSize(); i++) 
	{
		columns.at(i).update(engine);

		if (columns.at(i).isFull())
			filterGems();
	}
}

void Grid::filterGems() 
{
	for (int j = 0; j < columns.size(); j++)
	{
		if (columns.at(j).isDeleteReady())
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

				if(j < columns.size() - 2)
				if (columns.at(j).getGems().at(i).getGemType() == columns.at(j + 1).getGems().at(i).getGemType() &&
					columns.at(j).getGems().at(i).getGemType() == columns.at(j + 2).getGems().at(i).getGemType())
				{
					if (columns.at(i).isFull() && columns.at(i + 1).isFull() && columns.at(i + 2).isFull())
					{
						columns.at(j).markForDeletion(i);
						columns.at(j + 1).markForDeletion(i);
						columns.at(j + 2).markForDeletion(i);
					}
				}
			}
		}
	}

}
