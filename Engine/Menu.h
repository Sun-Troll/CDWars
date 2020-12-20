#pragma once

#include "World.h"

class Menu
{
public:
	Menu(const std::string& background_in);
	void DrawWorld(Graphics& gfx, const RectI& renderRect, const Font& f, const World& w) const;
private:
	Surface background;
	static constexpr Color cText{ 50, 50, 50 };
};