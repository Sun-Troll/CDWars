#pragma once

#include "World.h"

class Menu
{
public:
	enum class Select
	{
		Game,
		Divisions,
		Map
	};
public:
	Menu(const std::string& background_in, const std::string& wMinimap_in);
	void SetWorldCamPos(World& w, const VecF& pos) const;
	void ChangeSelect(const VecI& pos);
	bool ToggleArmyEditor(const VecI& pos) const;
	void DrawWorld(Graphics& gfx, const RectI& renderRect, const Font& f, const World& w) const;
private:
	const std::string UnitsToStr(Division::Unit units) const;
	const std::string DivToStr(const Army& player, int i) const;
	const std::string StateToStr(Army::State state) const;
private:
	static constexpr Color cText{ 50, 40, 20 };
	static constexpr int leftPadding = 8;
	static constexpr int minimapTop = 700;
	static constexpr int mapSize = 256;
	static constexpr float mapToMinimap = 63.9921875f;
	Surface background;
	Surface wMinimap;
	static constexpr VecF minimapLeftTop{ float(Graphics::gameWidth + leftPadding), float(minimapTop) };
	static constexpr VecF mapCorOffset{ minimapLeftTop.x + float(mapSize / 2), minimapLeftTop.y + float(mapSize / 2)  };
	static constexpr RectF minimapRect{ minimapLeftTop.x,
		minimapLeftTop.x + float(mapSize), minimapLeftTop.y, minimapLeftTop.y + float(mapSize) };

	static constexpr int bOff = 8;
	static constexpr int gameSetY = 20;
	static constexpr int divSetY = 60;
	static constexpr int mapSetY = 100;
	static constexpr int armyEditY = 635;
	static constexpr RectI gameSet{ Graphics::gameWidth + leftPadding, Graphics::ScreenWidth - 20, gameSetY, gameSetY + 35 };
	static constexpr RectI divSet{ Graphics::gameWidth + leftPadding, Graphics::ScreenWidth - 20, divSetY, divSetY + 35 };
	static constexpr RectI mapSet{ Graphics::gameWidth + leftPadding, Graphics::ScreenWidth - 20, mapSetY, mapSetY + 35 };
	static constexpr RectI armyEdit{ Graphics::gameWidth + leftPadding, Graphics::ScreenWidth - 20, armyEditY, armyEditY + 35 };
	Select sCur = Select::Map;
};