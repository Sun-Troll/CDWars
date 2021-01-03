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

	static constexpr int butTP = 9;
	static constexpr int butH = 35;
	static constexpr int butW = 35 - butTP;
	static constexpr int butSpaceX = 50;
	static constexpr int butSpaceY = 150;
	static constexpr VecI cLinesDecLT{ 250 , 55 };
	static constexpr VecI cLinesIncLT{ 250 + butSpaceX , 55 };
	static constexpr RectI cLinesDec{ cLinesDecLT.x - butTP, cLinesDecLT.x + butW, cLinesDecLT.y, cLinesDecLT.y + butH };
	static constexpr RectI cLinesInc{ cLinesIncLT.x - butTP, cLinesIncLT.x + butW, cLinesIncLT.y, cLinesIncLT.y + butH };
};