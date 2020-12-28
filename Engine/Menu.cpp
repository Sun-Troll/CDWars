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

void Menu::ChangeSelect(const VecI& pos)
{
	if (gameSet.ContainsPoint(pos))
	{
		sCur = Select::Game;
	}
	else if (divSet.ContainsPoint(pos))
	{
		sCur = Select::Divisions;
	}
	else if (mapSet.ContainsPoint(pos))
	{
		sCur = Select::Map;
	}
}

void Menu::DrawWorld(Graphics& gfx, const RectI& drawRect, const Font& f, const World& w) const
{
	gfx.DrawSprite(Graphics::gameWidth, 0, drawRect, background, SpriteEffect::Copy{});
	std::string money = "Money: " + std::to_string(w.GetMoney());
	std::string playerState = "State: ";
	switch (w.GetPlayer().GetState())
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
	const std::string playerPos = "Army position:\n" + std::to_string(w.GetPlayer().GetPos().x)
		+ '\n' + std::to_string(w.GetPlayer().GetPos().y);
	const std::string targetPos = "Target position:\n" + std::to_string(w.GetPlayer().GetTarget().x)
		+ '\n' + std::to_string(w.GetPlayer().GetTarget().y);
	const std::string camPosStr = "Camera position:\n" + std::to_string(w.GetCamPos().x)
		+ '\n' + std::to_string(w.GetCamPos().y);
	gfx.DrawRect(gameSet, cText);
	gfx.DrawRect(divSet, cText);
	gfx.DrawRect(mapSet, cText);
	f.DrawText("Game", { Graphics::gameWidth + leftPadding + 8, gameSetY }, cText, drawRect, gfx);
	f.DrawText("Divisions", { Graphics::gameWidth + leftPadding + 8, divSetY }, cText, drawRect, gfx);
	f.DrawText("Map", { Graphics::gameWidth + leftPadding + 8, mapSetY }, cText, drawRect, gfx);
	switch (sCur)
	{
	case Menu::Select::Game:
		break;
	case Menu::Select::Divisions:
	{
		const Army& pa = w.GetPlayer();
		const std::string dc = "C: " + DivToStr(pa, 1);
		const std::string dl = "L: " + DivToStr(pa, 0);
		const std::string dr = "R: " + DivToStr(pa, 2);
		const std::string db = "B: " + DivToStr(pa, 3);
		f.DrawText(money, { Graphics::gameWidth + leftPadding, 150 }, cText, drawRect, gfx);
		f.DrawText(dc, { Graphics::gameWidth + leftPadding, 190 }, cText, drawRect, gfx);
		f.DrawText(dl, { Graphics::gameWidth + leftPadding, 260 }, cText, drawRect, gfx);
		f.DrawText(dr, { Graphics::gameWidth + leftPadding, 330 }, cText, drawRect, gfx);
		f.DrawText(db, { Graphics::gameWidth + leftPadding, 400 }, cText, drawRect, gfx);
	}
		break;
	case Menu::Select::Map:
		f.DrawText(money, { Graphics::gameWidth + leftPadding, 290 }, cText, drawRect, gfx);
		f.DrawText(playerState, { Graphics::gameWidth + leftPadding, 330 }, cText, drawRect, gfx);
		f.DrawText(playerPos, { Graphics::gameWidth + leftPadding, 370 }, cText, drawRect, gfx);
		f.DrawText(targetPos, { Graphics::gameWidth + leftPadding, 480 }, cText, drawRect, gfx);
		f.DrawText(camPosStr, { Graphics::gameWidth + leftPadding, 590 }, cText, drawRect, gfx);
		break;
	default:
		break;
	}
	gfx.DrawSprite(Graphics::gameWidth + leftPadding, minimapTop, drawRect, wMinimap, SpriteEffect::Copy{});
	for (const Army& a : w.GetEnemies())
	{
		if (w.GetPlayer().Detect(a))
		{
			gfx.DrawCross(VecI(a.GetPos() / mapToMinimap + mapCorOffset), 2, Colors::Red);
		}
	}
	gfx.DrawCross(VecI(w.GetCamPos() / mapToMinimap + mapCorOffset), 6, Colors::Black);
	gfx.DrawCross(VecI(w.GetPlayer().GetPos() / mapToMinimap + mapCorOffset), 5, Colors::Blue);
	gfx.DrawCross(VecI(w.GetPlayer().GetTarget() / mapToMinimap + mapCorOffset), 4, Colors::White);
}

const std::string Menu::UnitsToStr(Division::Unit units) const
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

const std::string Menu::DivToStr(const Army& player, int i) const
{
	return std::string(UnitsToStr(player.GetUnits(i)) + "\n  L:" + std::to_string(player.GetLines(i))
		+ " G:" + std::to_string(player.GetGear(i)) + " T:" + std::to_string(player.GetTraining(i)));
}
