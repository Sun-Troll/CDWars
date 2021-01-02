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
}
