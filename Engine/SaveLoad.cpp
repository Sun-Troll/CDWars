#include "SaveLoad.h"
#include <fstream>
#include <cassert>

void SaveLoad::Save(int n, const Army& player) const
{
	assert(n > 0);
	std::ofstream out(files + std::to_string(n) + fExtension, std::ios::binary);
	out.write(reinterpret_cast<const char*>(&player), sizeof(player));
}

bool SaveLoad::Load(int n, Army& player) const
{
	assert(n > 0);
	std::ifstream in(files + std::to_string(n) + fExtension, std::ios::binary);
	if (in)
	{
		in.read(reinterpret_cast<char*>(&player), sizeof(player));
		return true;
	}
	return false;
}
