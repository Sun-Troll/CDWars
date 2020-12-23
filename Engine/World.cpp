#include "World.h"
#include <thread>
#include <functional>
#include <algorithm>

World::World(const std::string& mapLT_in, const std::string& mapRT_in,
	const std::string& mapLB_in, const std::string& mapRB_in,
	const std::string& armyPlayer_in, const std::string& armyEnemy_in,
	const std::string& armyTarget_in)
	:
	armyPlayer(armyPlayer_in),
	armyEnemy(armyEnemy_in),
	armyTarget(armyTarget_in),
	playerArmyDrawPos(VecI(player.GetPos()) - VecI{ camRenderX, camRenderY }),
	playerTargetDrawPos(VecI(player.GetTarget()) - VecI{ camRenderX, camRenderY })
{
	//test code
	mapLT = Surface{ int(worldRect.GetWidth() / 2), int(worldRect.GetHeight() / 2), forrest };
	mapRT = Surface{ int(worldRect.GetWidth() / 2), int(worldRect.GetHeight() / 2), swamp };
	mapLB = Surface{ int(worldRect.GetWidth() / 2), int(worldRect.GetHeight() / 2), dessert };
	mapRB = Surface{ int(worldRect.GetWidth() / 2), int(worldRect.GetHeight() / 2), tundra };
	//main code
	/*std::thread t1(&World::LoadMap, std::ref(*this), std::ref(mapLT), std::cref(mapLT_in));
	std::thread t2(&World::LoadMap, std::ref(*this), std::ref(mapRT), std::cref(mapRT_in));
	std::thread t3(&World::LoadMap, std::ref(*this), std::ref(mapLB), std::cref(mapLB_in));
	LoadMap(mapRB, mapRB_in);
	t1.join();
	t2.join();
	t3.join();*/
	assert(worldRect.GetWidth() / 2 == mapLT.GetWidth());
	assert(worldRect.GetHeight() / 2 == mapLT.GetHeight());
	assert(worldRect.GetWidth() / 2 == mapRT.GetWidth());
	assert(worldRect.GetHeight() / 2 == mapRT.GetHeight());
	assert(worldRect.GetWidth() / 2 == mapLB.GetWidth());
	assert(worldRect.GetHeight() / 2 == mapLB.GetHeight());
	assert(worldRect.GetWidth() / 2 == mapRB.GetWidth());
	assert(worldRect.GetHeight() / 2 == mapRB.GetHeight());

	assert(armyPlayer.GetWidth() / 2 == halfArmySprite.x);
	assert(armyPlayer.GetHeight() / 2 == halfArmySprite.y);
	assert(armyEnemy.GetWidth() / 2 == halfArmySprite.x);
	assert(armyEnemy.GetHeight() / 2 == halfArmySprite.y);
	assert(armyTarget.GetWidth() / 2 == halfArmySprite.x);
	assert(armyTarget.GetHeight() / 2 == halfArmySprite.y);
}

void World::MoveCamera(bool left, bool right, bool up, bool down, float dt)
{
	VecF move{ 0.0f, 0.0f };
	if (left)
	{
		--move.x;
	}
	if (right)
	{
		++move.x;
	}
	if (up)
	{
		--move.y;
	}
	if (down)
	{
		++move.y;
	}
	cameraPos += move * cameraMoveSpeed * dt;
}

void World::SetCamera(const VecF& pos)
{
	cameraPos = pos;
}

void World::ClampCamera()
{
	cameraPos.x = std::max(std::min(cameraPos.x, worldRect.right), worldRect.left);
	cameraPos.y = std::max(std::min(cameraPos.y, worldRect.bottom), worldRect.top);
}

const VecF& World::GetCamPos() const
{
	return cameraPos;
}

void World::PlayerSetTarget(VecF target)
{
	target += cameraPos;
	target.x = std::max(std::min(target.x - Graphics::gameWidth / 2, worldRect.right), worldRect.left);
	target.y = std::max(std::min(target.y - Graphics::ScreenHeight / 2, worldRect.bottom), worldRect.top);
	player.SetTarget(target);
}

const VecF& World::GetPlayerPos() const
{
	return player.GetPos();
}

const VecF& World::GetPlayerTarget() const
{
	return player.GetTarget();
}

void World::DrawPrepare()
{
	camRenderX = int(cameraPos.x) - Graphics::gameWidth / 2;
	camRenderY = int(cameraPos.y) - Graphics::ScreenHeight / 2;
	const VecI offset = VecI{ camRenderX, camRenderY } + halfArmySprite;
	playerArmyDrawPos = VecI(player.GetPos()) - offset;
	playerTargetDrawPos = VecI(player.GetTarget()) - offset;
}

void World::DrawMap(Graphics& gfx, const RectI& drawRect) const
{
	gfx.DrawSprite(left - camRenderX, top - camRenderY, drawRect, mapLT, SpriteEffect::Copy{});
	gfx.DrawSprite(0 - camRenderX, top - camRenderY, drawRect, mapRT, SpriteEffect::Copy{});
	gfx.DrawSprite(left - camRenderX, 0 - camRenderY, drawRect, mapLB, SpriteEffect::Copy{});
	gfx.DrawSprite(0 - camRenderX, 0 - camRenderY, drawRect, mapRB, SpriteEffect::Copy{});
}

void World::DrawArmies(Graphics& gfx, const RectI& drawRect) const
{
	gfx.DrawSprite(playerArmyDrawPos.x, playerArmyDrawPos.y,
		drawRect, armyPlayer, SpriteEffect::Chroma{ Colors::White });
	gfx.DrawSprite(playerTargetDrawPos.x, playerTargetDrawPos.y,
		drawRect, armyTarget, SpriteEffect::Chroma{ Colors::White });
}

void World::DrawHeading(Graphics& gfx) const
{
	gfx.DrawLine(VecF(playerArmyDrawPos + halfArmySprite), VecF(playerTargetDrawPos + halfArmySprite), Colors::Blue);
}

void World::LoadMap(Surface& map, const std::string& map_in)
{
	map = Surface{ map_in };
}
