#pragma once

#include "Army.h"
#include <string>

class SaveLoad
{
public:
	void Save(int n, const Army& player, const std::vector<Army>& enemies) const;
	bool Load(int n, Army& player, std::vector<Army>& enemies) const;
private:
	void ArmySave(std::ofstream& out, const Army& army) const;
	Army ArmyLoad(std::ifstream& in) const;
private:
	const std::string fileName = "Saves\\save";
	const std::string fExtension = ".dat";
};