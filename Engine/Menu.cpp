#include "Menu.h"
#include <cassert>

Menu::Menu(const std::string& background_in, const std::string& wMinimap_in)
	:
	background(background_in),
	wMinimap(wMinimap_in)
{
	assert(background.GetWidth() == Graphics::menuWidth);
	assert(background.GetHeight() == Graphics::ScreenHeight);
	assert(wMinimap.GetWidth() == mapSize);
	assert(wMinimap.GetHeight() == mapSize);
}

void Menu::SetWorldCamPos(World& w, const VecF& pos) const
{
	if (minimapRect.ContainsPoint(pos))
	{
		w.SetCamera((pos - mapCorOffset) * mapToMinimap);
	}
}

void Menu::DrawWorld(Graphics& gfx, const RectI& drawRect, const Font& f, const World& w) const
{
	gfx.DrawSprite(Graphics::gameWidth, 0, drawRect, background, SpriteEffect::Copy{});
	const std::string camPosStr = "Camera Pos:\n" + std::to_string(w.GetCamPos().x) + '\n' + std::to_string(w.GetCamPos().y);
	f.DrawText(camPosStr, { Graphics::gameWidth + leftPadding, 590 }, cText, drawRect, gfx);
	gfx.DrawSprite(Graphics::gameWidth + leftPadding, minimapTop, drawRect, wMinimap, SpriteEffect::Copy{});
	gfx.DrawCross(VecI(w.GetCamPos() / mapToMinimap + mapCorOffset), 6, Colors::Black);
	gfx.DrawCross(VecI(w.GetPlayerPos() / mapToMinimap + mapCorOffset), 5, Colors::Blue);
	gfx.DrawCross(VecI(w.GetPlayerTarget() / mapToMinimap + mapCorOffset), 4, Colors::White);
}
