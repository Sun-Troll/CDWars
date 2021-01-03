#pragma once

#include "Font.h"
#include "Army.h"

class ArmyEditor
{
public:
	ArmyEditor(const std::string& background_in, Army& player_in);
	void Draw(Graphics& gfx, const RectI& drawRect, const Font& f) const;
private:
	const std::string UnitsToStr(Division::Unit units) const;
	const std::string DivToStr(int i) const;
private:
	static constexpr Color cText{ 50, 40, 20 };
	static constexpr int padBase = 16;
	Surface background;
	Army& player;
	Army temp = player;
};