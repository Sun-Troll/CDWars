#include "ArmyEditor.h"
#include <cassert>

ArmyEditor::ArmyEditor(const std::string& background_in, Army& player_in)
	:
	background(background_in),
	player(player_in)
{
	assert(background.GetWidth() == Graphics::gameWidth);
	assert(background.GetHeight() == Graphics::ScreenHeight);
}

void ArmyEditor::Draw(Graphics& gfx, const RectI& drawRect, const Font& f) const
{
	gfx.DrawSprite(0, 0, drawRect, background, SpriteEffect::Copy{});
	const std::string divC = "Center: " + DivToStr(1);
	const std::string divL = "Left: " + DivToStr(0);
	const std::string divR = "Right: " + DivToStr(2);
	const std::string divB = "Back: " + DivToStr(3);
	f.DrawText(divC, { padBase, 20 }, cText, drawRect, gfx);
	f.DrawText(divL, { padBase, 170 }, cText, drawRect, gfx);
	f.DrawText(divR, { padBase, 320 }, cText, drawRect, gfx);
	f.DrawText(divB, { padBase, 470 }, cText, drawRect, gfx);
	DrawLinesBut(gfx, drawRect, f, cLinesDecLT, cLinesIncLT, cLinesDec, cLinesInc);
	DrawLinesBut(gfx, drawRect, f, lLinesDecLT, lLinesIncLT, lLinesDec, lLinesInc);
	DrawLinesBut(gfx, drawRect, f, rLinesDecLT, rLinesIncLT, rLinesDec, rLinesInc);
	DrawLinesBut(gfx, drawRect, f, bLinesDecLT, bLinesIncLT, bLinesDec, bLinesInc);
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

void ArmyEditor::DrawLinesBut(Graphics& gfx, const RectI& drawRect, const Font& f,
	const VecI& lvd, const VecI& lvi, const RectI& lrd, const RectI& lri) const
{
	gfx.DrawRect(lrd, cText);
	gfx.DrawRect(lri, cText);
	f.DrawText("-", lvd, cText, drawRect, gfx);
	f.DrawText("+", lvi, cText, drawRect, gfx);
}
