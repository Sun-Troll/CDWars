#include "SaveLoad.h"
#include <fstream>

void SaveLoad::Save(const std::string& file, const Army& player) const
{
	std::ofstream out(file, std::ios::binary);
	out.write(reinterpret_cast<const char*>(&player), sizeof(player));
}

bool SaveLoad::Load(const std::string& file, Army& player) const
{
	std::ifstream in(file, std::ios::binary);
	if (in)
	{
		in.read(reinterpret_cast<char*>(&player), sizeof(player));
		return true;
	}
	return false;
}
