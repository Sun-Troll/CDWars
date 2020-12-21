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
		w.SetCamera((pos - minimapLeftTop - VecF{ float(mapSize / 2), float(mapSize / 2) }) * 63.9921875f);
	}
}

void Menu::DrawWorld(Graphics& gfx, const RectI& drawRect, const Font& f, const World& w) const
{
	gfx.DrawSprite(Graphics::gameWidth, 0, drawRect, background, SpriteEffect::Copy{});
	const std::string camPosStr = "Camera Pos:\n" + std::to_string(w.GetCamPos().x) + '\n' + std::to_string(w.GetCamPos().y);
	f.DrawText(camPosStr, { Graphics::gameWidth + 8, 590 }, cText, drawRect, gfx);
	gfx.DrawSprite(Graphics::gameWidth + leftPadding, minimapTop, drawRect, wMinimap, SpriteEffect::Copy{});
	gfx.DrawCross(VecI(w.GetCamPos() / 63.9921875f + minimapLeftTop + VecF{ float(mapSize / 2), float(mapSize / 2) }),
		6, Colors::Black);
}
