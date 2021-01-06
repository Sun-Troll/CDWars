#include "ArmyEditor.h"
#include <cassert>

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

