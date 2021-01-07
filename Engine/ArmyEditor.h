#pragma once

#include "Font.h"
#include "Army.h"

class ArmyEditor
{
public:
	ArmyEditor(const std::string& background_in, Army& player_in);
	void Draw(Graphics& gfx, const RectI& drawRect, const Font& f) const;
	void CheckButtons(const VecI& pos);
private:
	const std::string UnitsToStr(Division::Unit units) const;
	const std::string DivToStr(int i) const;
	const std::string GearCosts(int i) const;
	int CalcTotalCost(int curGear, int prewGear) const;
	int CalcBuyCost(int curGear) const;
	int CalcSellCost(int curGear) const;
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
	static constexpr int butGearYpos = butYpos + 35;
	std::vector<VecI> butLinesLT;
	std::vector<RectI> butLinesR;
	std::vector<VecI> butGearLT;
	std::vector<RectI> butGearR;
	std::vector<int> gearCost;
	std::vector<int> gearSell;
	std::vector<int> gearBuy;
	static constexpr float gearCostBase = 100.0f;
	static constexpr float gearCostIncrease = 1.05f;
	static constexpr int gearCostPad = padBase + 350;

	static constexpr VecI resetTL{ padBase * 2, Graphics::ScreenHeight - 50 };
	static constexpr VecI confirmTL{ resetTL.x + 190, resetTL.y };
	static constexpr RectI resetR{ resetTL.x, resetTL.x + 90, resetTL.y, resetTL.y + 35 };
	static constexpr RectI confirmR{ confirmTL.x, confirmTL.x + 126, confirmTL.y, confirmTL.y + 35 };
};