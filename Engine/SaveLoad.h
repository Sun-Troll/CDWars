#pragma once

#include "Army.h"
#include <string>

class SaveLoad
{
public:
	void Save(int n, const Army& player) const;
	bool Load(int n, Army& player) const;
private:
	const std::string files = "Saves\\save";
	const std::string fExtension = ".dat";
};