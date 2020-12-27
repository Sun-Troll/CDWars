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
	std::string money = "Money: " + std::to_string(w.GetMoney());
	std::string playerState = "State: ";
	switch (w.GetPlayerState())
	{
	case Army::State::March:
		playerState += "March";
		break;
	case Army::State::Scout:
		playerState += "Scout";
		break;
	case Army::State::Sneak:
		playerState += "Sneak";
		break;
	default:
		break;
	}
	const std::string playerPos = "Army position:\n" + std::to_string(w.GetPlayerPos().x)
		+ '\n' + std::to_string(w.GetPlayerPos().y);
	const std::string targetPos = "Target position:\n" + std::to_string(w.GetPlayerTarget().x)
		+ '\n' + std::to_string(w.GetPlayerTarget().y);
	const std::string camPosStr = "Camera position:\n" + std::to_string(w.GetCamPos().x)
		+ '\n' + std::to_string(w.GetCamPos().y);
	f.DrawText(money, { Graphics::gameWidth + leftPadding, 290 }, cText, drawRect, gfx);
	f.DrawText(playerState, { Graphics::gameWidth + leftPadding, 330 }, cText, drawRect, gfx);
	f.DrawText(playerPos, { Graphics::gameWidth + leftPadding, 370 }, cText, drawRect, gfx);
	f.DrawText(targetPos, { Graphics::gameWidth + leftPadding, 480 }, cText, drawRect, gfx);
	f.DrawText(camPosStr, { Graphics::gameWidth + leftPadding, 590 }, cText, drawRect, gfx);
	gfx.DrawSprite(Graphics::gameWidth + leftPadding, minimapTop, drawRect, wMinimap, SpriteEffect::Copy{});
	for (const Army& a : w.GetEnemies())
	{
		if (w.GetPlayer().Detect(a))
		{
			gfx.DrawCross(VecI(a.GetPos() / mapToMinimap + mapCorOffset), 2, Colors::Red);
		}
	}
	gfx.DrawCross(VecI(w.GetCamPos() / mapToMinimap + mapCorOffset), 6, Colors::Black);
	gfx.DrawCross(VecI(w.GetPlayerPos() / mapToMinimap + mapCorOffset), 5, Colors::Blue);
	gfx.DrawCross(VecI(w.GetPlayerTarget() / mapToMinimap + mapCorOffset), 4, Colors::White);
}
