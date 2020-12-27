#pragma once
#include "Graphics.h"
#include "Font.h"
#include "Army.h"
#include <random>

class World
{
public:
	World(const std::string& mapLT_in, const std::string& mapRT_in,
		const std::string& mapLB_in, const std::string& mapRB_in,
		const std::string& armyPlayer_in, const std::string& armyEnemy_in,
		const std::string& armyTarget_in);
	//camera
	void MoveCamera(bool left, bool right, bool up, bool down, float dt);
	void SetCamera(const VecF& pos);
	void ClampCamera();
	const VecF& GetCamPos() const;
	//armies
	void PlayerSetTarget(VecF target);
	void PlayerSetState(Army::State state);
	void ArmiesMove(float dt);
	void EnemiesSetTarget(std::mt19937& rng);
	void SpawnEnemies(std::mt19937& rng);
	const VecF& GetPlayerPos() const;
	const VecF& GetPlayerTarget() const;
	const Army::State GetPlayerState() const;
	const Army& GetPlayer() const;
	const std::vector<Army>& GetEnemies() const;
	//misc
	int GetMoney() const;
	//draw
	void DrawPrepare();
	void DrawMap(Graphics& gfx, const RectI& drawRect) const;
	void DrawArmies(Graphics& gfx, const RectI& drawRect) const;
	void DrawHeading(Graphics& gfx) const;
	void DrawDetect(Graphics& gfx) const;
private:
	void LoadMap(Surface& map, const std::string& map_in);
private:
	static constexpr RectF worldRect{ -8191.0f, 8191.0f, -8191.0f, 8191.0f };
	static constexpr int left = int(worldRect.left);
	static constexpr int top = int(worldRect.top);
	Surface mapLT;
	Surface mapRT;
	Surface mapLB;
	Surface mapRB;
	Surface armyPlayer;
	Surface armyEnemy;
	Surface armyTarget;
	static constexpr Color forrest{ 129, 225, 101 };
	static constexpr Color swamp{ 93, 101, 9 };
	static constexpr Color dessert{ 244, 234, 72 };
	static constexpr Color stonyDes{ 130, 75, 13 };
	static constexpr Color taiga{ 44, 198, 162 };
	static constexpr Color tundra{ 183, 215, 239 };
	static constexpr float cameraMoveSpeed = 1000.0f;

	VecF cameraPos{ 0.0f, 0.0f };
	int camRenderX = int(cameraPos.x) - Graphics::gameWidth / 2;
	int camRenderY = int(cameraPos.y) - Graphics::ScreenHeight / 2;

	static constexpr VecI halfArmySprite{ 16, 16 };
	Army player{ Army::State::March, { -8000.0f, 0.0f }, Division::Unit::Archer, 4, 10, 10,
	Division::Unit::Knight, 2, 10, 10, Division::Unit::Knight, 2, 10, 10, Division::Unit::Archer, 3, 12, 12 };
	VecI playerArmyDrawPos;
	VecI playerTargetDrawPos;
	int playerDetectRad;

	int money = 1000;

	std::vector<Army> enemies;
	std::vector<VecI> enemiesDraw;
	const std::uniform_int_distribution<int> posDist{ -8190, 8190 };
	const std::uniform_int_distribution<int> stateDist{ 0, 999 };
	const std::uniform_int_distribution<int> gearTraining{ 1, 100 };
	static constexpr int nUnitTypes = 3;
	const std::uniform_int_distribution<int> armyUnits{ 0, nUnitTypes - 1 };
	static constexpr int stateScoutChance = 300;
	static constexpr int StateSneakChance = 200;
	static constexpr std::size_t nEnemies = 100;
	static constexpr float minSpawnDistSq = 5000000;
};