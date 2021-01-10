#pragma once

#include "Army.h"
#include <string>

class SaveLoad
{
public:
	void Save(const std::string& file, const Army& player) const;
	bool Load(const std::string& file, Army& player) const;
private:

};