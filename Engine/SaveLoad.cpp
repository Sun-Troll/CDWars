#include "SaveLoad.h"
#include <fstream>
#include <cassert>

void SaveLoad::Save(int n, int money, const Army& player, const std::vector<Army>& enemies) const
{
	assert(n > 0);
	std::ofstream out(fileName + std::to_string(n) + fExtension, std::ios::binary);

	out.write(reinterpret_cast<const char*>(&money), sizeof(money));

	ArmySave(out, player);

	for (const Army& a : enemies)
	{
		ArmySave(out, a);
	}
} // 9 + 52 + 8 = 4 + 69 * 101 = 6973

int SaveLoad::Load(int n, int money, Army& player, std::vector<Army>& enemies) const
{
	assert(n > 0);
	std::ifstream in(fileName + std::to_string(n) + fExtension, std::ios::binary);
	if (in)
	{
		money *= -1;
		int moneySave;
		in.read(reinterpret_cast<char*>(&moneySave), sizeof(moneySave));
		money += moneySave;

		player = ArmyLoad(in);

		for (Army& a : enemies)
		{
			a = ArmyLoad(in);
		}
	}
	return money;
}

void SaveLoad::ArmySave(std::ofstream& out, const Army& army) const
{
	const Army::State state = army.GetState();
	const float posX = army.GetPos().x;
	const float posY = army.GetPos().y;
	out.write(reinterpret_cast<const char*>(&state), sizeof(state));
	out.write(reinterpret_cast<const char*>(&posX), sizeof(posX));
	out.write(reinterpret_cast<const char*>(&posY), sizeof(posY));

	for (int i = 0; i < 4; ++i)
	{
		const Division::Unit unit = army.GetUnits(i);
		const int lines = army.GetLines(i);
		const int gear = army.GetGear(i);
		const int training = army.GetTraining(i);
		out.write(reinterpret_cast<const char*>(&unit), sizeof(unit));
		out.write(reinterpret_cast<const char*>(&lines), sizeof(lines));
		out.write(reinterpret_cast<const char*>(&gear), sizeof(gear));
		out.write(reinterpret_cast<const char*>(&training), sizeof(training));
	}

	const float targetX = army.GetTarget().x;
	const float targetY = army.GetTarget().y;
	out.write(reinterpret_cast<const char*>(&targetX), sizeof(targetX));
	out.write(reinterpret_cast<const char*>(&targetY), sizeof(targetY));
}

Army SaveLoad::ArmyLoad(std::ifstream& in) const
{
	assert(in);
	Army::State state;
	float posX;
	float posY;
	in.read(reinterpret_cast<char*>(&state), sizeof(state));
	in.read(reinterpret_cast<char*>(&posX), sizeof(posX));
	in.read(reinterpret_cast<char*>(&posY), sizeof(posY));

	Division::Unit units[4];
	int lines[4];
	int gear[4];
	int training[4];
	for (int i = 0; i < 4; ++i)
	{
		in.read(reinterpret_cast<char*>(&units[i]), sizeof(units[i]));
		in.read(reinterpret_cast<char*>(&lines[i]), sizeof(lines[i]));
		in.read(reinterpret_cast<char*>(&gear[i]), sizeof(gear[i]));
		in.read(reinterpret_cast<char*>(&training[i]), sizeof(training[i]));
	}

	float targetX;
	float targetY;
	in.read(reinterpret_cast<char*>(&targetX), sizeof(targetX));
	in.read(reinterpret_cast<char*>(&targetY), sizeof(targetY));
	Army temp{ state, { posX, posY }, units[0], lines[0], gear[0], training[0], units[1], lines[1], gear[1], training[1],
		units[2], lines[2], gear[2], training[2], units[3], lines[3], gear[3], training[3] };
	temp.SetTarget({ targetX, targetY });

	return temp;
}
