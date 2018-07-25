#include <List>
#include <random>
#include "Gem.h"

using namespace std;

#pragma once
class Column
{
protected:
	list<Gem> gems;
	
public:
	Column();
	virtual ~Column();

};

