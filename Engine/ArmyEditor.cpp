#include "ArmyEditor.h"
#include <cassert>
#include <cmath>

ArmyEditor::ArmyEditor(const std::string& background_in, Army& player_in)
	:
	background(background_in),
	player(player_in)
{
	assert(background.GetWidth() == Graphics::gameWidth);
	assert(background.GetHeight() == Graphics::ScreenHeight);

	butLinesLT.reserve(8);
	for (int n = 0; n < 4; ++n)
	{
		butLinesLT.emplace_back(butXpos, butYpos + butSpaceY * n);
		butLinesLT.emplace_back(butXpos + butSpaceX, butYpos + butSpaceY * n);
	}
	butLinesR.reserve(8);
	for (int n = 0; n < butLinesLT.size(); ++n)
	{
		butLinesR.emplace_back(butLinesLT[n].x - butTP, butLinesLT[n].x + butW, butLinesLT[n].y, butLinesLT[n].y + butH);
	}
	butGearLT.reserve(8);
	for (int n = 0; n < 4; ++n)
	{
		butGearLT.emplace_back(butXpos, butGearYpos + butSpaceY * n);
		butGearLT.emplace_back(butXpos + butSpaceX, butGearYpos + butSpaceY * n);
	}
	butGearR.reserve(8);
	for (int n = 0; n < butGearLT.size(); ++n)
	{
		butGearR.emplace_back(butGearLT[n].x - butTP, butGearLT[n].x + butW, butGearLT[n].y, butGearLT[n].y + butH);
	}

	gearCost.resize(4);
	gearSell.reserve(4);
	for (int i = 0; i < 4; ++i)
	{
		gearSell.push_back(CalcSellCost(temp.GetGear(i)));
	}
	gearBuy.reserve(4);
	for (int i = 0; i < 4; ++i)
	{
		gearBuy.push_back(CalcBuyCost(temp.GetGear(i)));
	}
}

void ArmyEditor::Draw(Graphics& gfx, const RectI& drawRect, const Font& f) const
{
	gfx.DrawSprite(0, 0, drawRect, background, SpriteEffect::Copy{});
	const std::string divL = "Left: " + DivToStr(0);
	const std::string divC = "Center: " + DivToStr(1);
	const std::string divR = "Right: " + DivToStr(2);
	const std::string divB = "Back: " + DivToStr(3);
	f.DrawText(divL, { padBase, 20 }, cText, drawRect, gfx);
	f.DrawText(divC, { padBase, 170 }, cText, drawRect, gfx);
	f.DrawText(divR, { padBase, 320 }, cText, drawRect, gfx);
	f.DrawText(divB, { padBase, 470 }, cText, drawRect, gfx);
	for (auto cur = butLinesLT.cbegin(), end = butLinesLT.cend(); cur < end; ++cur)
	{
		f.DrawText("-", *cur, cText, drawRect, gfx);
		++cur;
		f.DrawText("+", *cur, cText, drawRect, gfx);
	}
	for (const RectI& r : butLinesR)
	{
		gfx.DrawRect(r, cText);
	}
	for (auto cur = butGearLT.cbegin(), end = butGearLT.cend(); cur < end; ++cur)
	{
		f.DrawText("-", *cur, cText, drawRect, gfx);
		++cur;
		f.DrawText("+", *cur, cText, drawRect, gfx);
	}
	for (const RectI& r : butGearR)
	{
		gfx.DrawRect(r, cText);
	}
	f.DrawText(GearCosts(0), { gearCostPad, 90 }, cText, drawRect, gfx);
	f.DrawText(GearCosts(1), { gearCostPad, 240 }, cText, drawRect, gfx);
	f.DrawText(GearCosts(2), { gearCostPad, 390 }, cText, drawRect, gfx);
	f.DrawText(GearCosts(3), { gearCostPad, 540 }, cText, drawRect, gfx);
}

void ArmyEditor::CheckButtons(const VecI& pos)
{
	for (int i = 0; i < butLinesR.size(); ++i)
	{
		if (butLinesR[i].ContainsPoint(pos))
		{
			temp.SetLines(i / 2, i % 2);
		}
	}
	for (int i = 0; i < butGearR.size(); ++i)
	{
		if (butGearR[i].ContainsPoint(pos))
		{
			const int divI = i / 2;
			temp.SetGear(divI, i % 2);
			gearSell[divI] = CalcSellCost(temp.GetGear(divI));
			gearBuy[divI] = CalcBuyCost(temp.GetGear(divI));
		}
	}
}

const std::string ArmyEditor::UnitsToStr(Division::Unit units) const
{
	switch (units)
	{
	case Division::Unit::Knight:
		return "knight";
	case Division::Unit::Archer:
		return "archer";
	default:
		return "wrongUnit";
	}
}

const std::string ArmyEditor::DivToStr(int i) const
{
	return std::string(UnitsToStr(temp.GetUnits(i)) + "\n  lines: " + std::to_string(temp.GetLines(i))
		+ "\n  gear: " + std::to_string(temp.GetGear(i)) + "\n  training: " + std::to_string(temp.GetGear(i)));
}

const std::string ArmyEditor::GearCosts(int i) const
{
	return std::string("current: " + std::to_string(gearCost[i]) + " sell: " + std::to_string(gearSell[i])
		+ " buy: " + std::to_string(gearBuy[i]));
}

int ArmyEditor::CalcBuyCost(int curGear) const
{
	return int(gearCostBase * std::pow(gearCostIncrease, float(curGear - 10)));
}

int ArmyEditor::CalcSellCost(int curGear) const
{
	return int(gearCostBase * std::pow(gearCostIncrease, float(curGear - 11))) / 2;
}

