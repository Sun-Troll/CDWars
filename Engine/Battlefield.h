#pragma once

#include "World.h"
#include <unordered_map>

namespace std
{
	template<> struct hash<Color>
	{
		size_t operator()(const Color& c) const
		{
			return hash<unsigned int>{}(c.dword);
		}
	};
}

class Battlefield
{
public:
	enum class Terrain
	{
		Forrest,
		Swamp,
		Dessert,
		StonyDes,
		Taiga,
		Tundra
	};
public:
	Battlefield(Color terrain);
private:
	Terrain ColToTer(Color terrain) const;
private:
	static constexpr RectF battleRect{ -4095.0f, 4095.0f, -4095.0f, 4095.0f };
	static constexpr int left = int(battleRect.left);
	static constexpr int top = int(battleRect.top);
	const std::unordered_map<Color, Terrain> cToTer{
		{ World::GetForrest(), Terrain::Forrest },
		{ World::GetSwamp(), Terrain::Swamp },
		{ World::GetDessert(), Terrain::Dessert },
		{ World::GetStonyDes(), Terrain::StonyDes },
		{ World::GetTaiga(), Terrain::Taiga },
		{ World::GetTundra(), Terrain::Tundra }
	};
	const Terrain curTer;
};