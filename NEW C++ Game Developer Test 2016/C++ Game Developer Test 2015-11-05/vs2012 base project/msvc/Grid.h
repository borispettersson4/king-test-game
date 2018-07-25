#include <king/Engine.h>
#include <king/Updater.h>
#include "Gem.h"

#pragma once
class Grid : public King::Updater
{
private:

public:

	Grid();
	virtual ~Grid();
	Gem grid[];

};

