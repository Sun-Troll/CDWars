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
	void DrawLinesBut(Graphics& gfx, const RectI& drawRect, const Font& f,
		const VecI& lvd, const VecI& lvi, const RectI& lrd, const RectI& lri) const;
private:
	static constexpr Color cText{ 50, 40, 20 };
	static constexpr int padBase = 16;
	Surface background;
	Army& player;
	Army temp = player;

	static constexpr int butTP = 9;
	static constexpr int butH = 35;
	static constexpr int butW = 35 - butTP;
	static constexpr int butXpos = 250;
	static constexpr int butYpos = 55;
	static constexpr int butSpaceX = 50;
	static constexpr int butSpaceY = 150;
	static constexpr VecI cLinesDecLT{ butXpos , butYpos };
	static constexpr VecI cLinesIncLT{ butXpos + butSpaceX , butYpos };
	static constexpr VecI lLinesDecLT{ butXpos , butYpos + butSpaceY };
	static constexpr VecI lLinesIncLT{ butXpos + butSpaceX , butYpos + butSpaceY };
	static constexpr VecI rLinesDecLT{ butXpos , butYpos + butSpaceY * 2 };
	static constexpr VecI rLinesIncLT{ butXpos + butSpaceX , butYpos + butSpaceY * 2 };
	static constexpr VecI bLinesDecLT{ butXpos , butYpos + butSpaceY * 3 };
	static constexpr VecI bLinesIncLT{ butXpos + butSpaceX , butYpos + butSpaceY * 3 };
	static constexpr RectI cLinesDec{ cLinesDecLT.x - butTP, cLinesDecLT.x + butW, cLinesDecLT.y, cLinesDecLT.y + butH };
	static constexpr RectI cLinesInc{ cLinesIncLT.x - butTP, cLinesIncLT.x + butW, cLinesIncLT.y, cLinesIncLT.y + butH };
	static constexpr RectI lLinesDec{ lLinesDecLT.x - butTP, lLinesDecLT.x + butW, lLinesDecLT.y, lLinesDecLT.y + butH };
	static constexpr RectI lLinesInc{ lLinesIncLT.x - butTP, lLinesIncLT.x + butW, lLinesIncLT.y, lLinesIncLT.y + butH };
	static constexpr RectI rLinesDec{ rLinesDecLT.x - butTP, rLinesDecLT.x + butW, rLinesDecLT.y, rLinesDecLT.y + butH };
	static constexpr RectI rLinesInc{ rLinesIncLT.x - butTP, rLinesIncLT.x + butW, rLinesIncLT.y, rLinesIncLT.y + butH };
	static constexpr RectI bLinesDec{ bLinesDecLT.x - butTP, bLinesDecLT.x + butW, bLinesDecLT.y, bLinesDecLT.y + butH };
	static constexpr RectI bLinesInc{ bLinesIncLT.x - butTP, bLinesIncLT.x + butW, bLinesIncLT.y, bLinesIncLT.y + butH };
};