#pragma once

#include "World.h"

class Menu
{
public:
	Menu(const std::string& background_in, const std::string& wMinimap_in);
	void SetWorldCamPos(World& w, const VecF& pos) const;
	void DrawWorld(Graphics& gfx, const RectI& renderRect, const Font& f, const World& w) const;
private:
	static constexpr Color cText{ 50, 40, 20 };
	static constexpr int leftPadding = 8;
	static constexpr int minimapTop = 700;
	static constexpr int mapSize = 256;
	Surface background;
	Surface wMinimap;
	static constexpr VecF minimapLeftTop{ float(Graphics::gameWidth + leftPadding), float(minimapTop) };
	static constexpr RectF minimapRect{ minimapLeftTop.x,
		minimapLeftTop.x + float(mapSize), minimapLeftTop.y, minimapLeftTop.y + float(mapSize) };
};