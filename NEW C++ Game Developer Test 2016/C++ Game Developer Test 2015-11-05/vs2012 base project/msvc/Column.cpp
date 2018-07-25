#include "Column.h"



Column::Column()
{
	uniform_int_distribution<> rand(0,4);

	for (int i; i < 8; i++) 
	{
		Gem tempGem(rand.a, 0, 0);
		//gems[i] = tempGem;
	}
}


Column::~Column()
{
}
