#include "Menu.h"

Menu::Menu(const std::string& background_in)
	:
	background(background_in)
{
}

void Menu::DrawWorld(Graphics& gfx, const RectI& drawRect, const Font& f, const World& w) const
{
	gfx.DrawSprite(Graphics::gameWidth, 0, background, SpriteEffect::Copy{});
	const std::string camPosStr = "Camera Pos:\n" + std::to_string(w.GetCamPos().x) + '\n' + std::to_string(w.GetCamPos().y);
	f.DrawText(camPosStr, { Graphics::gameWidth + 8, 890 }, cText, drawRect, gfx);
}
