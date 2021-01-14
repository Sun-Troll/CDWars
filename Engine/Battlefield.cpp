#include "Battlefield.h"
#include <cassert>

Battlefield::Battlefield(Color terrain)
	:
	curTer(ColToTer(terrain))
{
}

Battlefield::Terrain Battlefield::ColToTer(Color terrain) const
{
	assert(cToTer.find(terrain) != cToTer.end());
	return cToTer.find(terrain)->second;
}
