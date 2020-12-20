#pragma once
#include "Graphics.h"
#include "Font.h"

class World
{
public:
	World(const std::string& mapLT_in, const std::string& mapRT_in,
		const std::string& mapLB_in, const std::string& mapRB_in);
	void MoveCamera(bool left, bool right, bool up, bool down, float dt);
	void SetCamera(const VecF& pos);
	void ClampCamera();
	const VecF& GetCamPos() const;
	void DrawPrepare();
	void DrawMap(Graphics& gfx, const RectI& DrawRect) const;
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
	static constexpr Color forrest{ 129, 225, 101 };
	static constexpr Color swamp{ 93, 101, 9 };
	static constexpr Color dessert{ 244, 234, 72 };
	static constexpr Color stonyDes{ 130, 75, 13 };
	static constexpr Color taiga{ 44, 198, 162 };
	static constexpr Color tundra{ 183, 215, 239 };
	static constexpr float cameraMoveSpeed = 1000.0f;
	VecF cameraPos{ 0.0f, 0.0f };
	int camRenderX;
	int camRenderY;
};