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
	playerTargetDrawPos(VecI(player.GetTarget()) - VecI{ camRenderX, camRenderY }),
	playerDetectRad(int(player.GetDetectRad()))
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

	enemies.reserve(100);

	//enemies.emplace_back(Army{ Army::State::March, { -7000.0f, 800.0f } });
	//enemies.emplace_back(Army{ Army::State::March, { -7500.0f, 400.0f } });
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

void World::PlayerSetState(Army::State state)
{
	player.SwitchState(state);
}

void World::ArmiesMove(float dt)
{
	player.Move(dt);
	for (Army& a : enemies)
	{
		a.Move(dt);
	}
}

void World::EnemiesSetTarget(std::mt19937& rng)
{
	for (Army& a : enemies)
	{
		if (a.Detect(player))
		{
			a.SetTarget(player.GetPos());
		}
		else
		{
			if (a.GetPos() == a.GetTarget())
			{
				a.SetTarget({ float(posDist(rng)), float(posDist(rng)) });
			}
		}
	}
}

void World::SpawnEnemies(std::mt19937& rng)
{
	while (enemies.size() < nEnemies)
	{
		VecF spawnPos{ 0.0f, 0.0f };
		do
		{
			spawnPos.x = float(posDist(rng));
			spawnPos.y = float(posDist(rng));
		} while (VecF{ player.GetPos() - spawnPos }.GetLengthSq() < minSpawnDistSq);

		const int stateVal = stateDist(rng);
		int cutoff = 0;
		Army::State spawnState;
		if (stateVal < (cutoff += stateScoutChance))
		{
			spawnState = Army::State::Scout;
		}
		else if (stateVal < (cutoff += StateSneakChance))
		{
			spawnState = Army::State::Sneak;
		}
		else
		{
			spawnState = Army::State::March;
		}
		assert(cutoff < 1000);

		Division::Unit unitL;
		Division::Unit unitC;
		Division::Unit unitR;
		Division::Unit unitB;
		int linesL;
		int linesC;
		int linesR;
		int linesB;
		const int unitType = armyUnits(rng);
		switch (unitType)
		{
		case 0:
			unitL = Division::Unit::Knight;
			unitC = Division::Unit::Archer;
			unitR = Division::Unit::Knight;
			unitB = Division::Unit::Archer;
			linesL = 2;
			linesC = 4;
			linesR = 2;
			linesB = 3;
			break;
		case 1:
			unitL = Division::Unit::Knight;
			unitC = Division::Unit::Knight;
			unitR = Division::Unit::Knight;
			unitB = Division::Unit::Archer;
			linesL = 2;
			linesC = 3;
			linesR = 2;
			linesB = 1;
			break;
		case 2:
			unitL = Division::Unit::Archer;
			unitC = Division::Unit::Knight;
			unitR = Division::Unit::Archer;
			unitB = Division::Unit::Archer;
			linesL = 6;
			linesC = 5;
			linesR = 6;
			linesB = 2;
			break;
		default:
			break;
		}

		const int gtBase = gearTraining(rng);
		const int aGear = (gtBase + gearTraining(rng)) / 2;
		const int aTraining = (gtBase + gearTraining(rng)) / 2;
		const int lG = (aGear + gearTraining(rng)) / 2;
		const int lT = (aTraining + gearTraining(rng)) / 2;
		const int cG = (aGear + gearTraining(rng)) / 2;
		const int cT = (aTraining + gearTraining(rng)) / 2;
		const int rG = (aGear + gearTraining(rng)) / 2;
		const int rT = (aTraining + gearTraining(rng)) / 2;
		const int bG = (aGear + gearTraining(rng)) / 2;
		const int bT = (aTraining + gearTraining(rng)) / 2;

		enemies.emplace_back(Army{ spawnState, spawnPos, unitL, linesL, lG, lT,
			unitC, linesC, cG, cT, unitR, linesR, rG, rT, unitB, linesB, bG, bT });
	}
}

Army& World::SetPlayer()
{
	return player;
}

const Army& World::GetPlayer() const
{
	return player;
}

const std::vector<Army>& World::GetEnemies() const
{
	return enemies;
}

int World::GetMoney() const
{
	return money;
}

void World::DrawPrepare()
{
	camRenderX = int(cameraPos.x) - Graphics::gameWidth / 2;
	camRenderY = int(cameraPos.y) - Graphics::ScreenHeight / 2;
	const VecI offset = VecI{ camRenderX, camRenderY } + halfArmySprite;
	playerArmyDrawPos = VecI(player.GetPos()) - offset;
	playerTargetDrawPos = VecI(player.GetTarget()) - offset;
	playerDetectRad = int(player.GetDetectRad());
	enemiesDraw.clear();
	for (const Army& a : enemies)
	{
		if (player.Detect(a))
		{
			enemiesDraw.emplace_back(VecI(a.GetPos()) - offset);
		}
	}
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
	for (const VecI& p : enemiesDraw)
	{
		gfx.DrawSprite(p.x, p.y, drawRect, armyEnemy, SpriteEffect::Chroma{ Colors::White });
	}
}

void World::DrawHeading(Graphics& gfx) const
{
	gfx.DrawLine(VecF(playerArmyDrawPos + halfArmySprite), VecF(playerTargetDrawPos + halfArmySprite), Colors::Blue);
}

void World::DrawDetect(Graphics & gfx) const
{
	const VecI detectCenter = playerArmyDrawPos + halfArmySprite;
	gfx.DrawCirc({ detectCenter, playerDetectRad }, Colors::Blue);
	gfx.DrawCirc({ detectCenter, playerDetectRad / 2 }, Colors::Blue);
}

void World::LoadMap(Surface& map, const std::string& map_in)
{
	map = Surface{ map_in };
}
