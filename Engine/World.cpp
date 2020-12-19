#include "World.h"
#include <thread>
#include <functional>

World::World(const std::string& mapLT_in, const std::string& mapRT_in,
	const std::string& mapLB_in, const std::string& mapRB_in)
{
	//test code
	/*mapLT = Surface{ int(worldRect.GetWidth() / 2), int(worldRect.GetHeight() / 2), forrest };
	mapRT = Surface{ int(worldRect.GetWidth() / 2), int(worldRect.GetHeight() / 2), swamp };
	mapLB = Surface{ int(worldRect.GetWidth() / 2), int(worldRect.GetHeight() / 2), dessert };
	mapRB = Surface{ int(worldRect.GetWidth() / 2), int(worldRect.GetHeight() / 2), tundra };*/
	//main code
	std::thread t1(&World::LoadMap, std::ref(*this), std::ref(mapLT), std::cref(mapLT_in));
	std::thread t2(&World::LoadMap, std::ref(*this), std::ref(mapRT), std::cref(mapRT_in));
	std::thread t3(&World::LoadMap, std::ref(*this), std::ref(mapLB), std::cref(mapLB_in));
	LoadMap(mapRB, mapRB_in);
	t1.join();
	t2.join();
	t3.join();
	assert(worldRect.GetWidth() / 2 == mapLT.GetWidth());
	assert(worldRect.GetHeight() / 2 == mapLT.GetHeight());
	assert(worldRect.GetWidth() / 2 == mapRT.GetWidth());
	assert(worldRect.GetHeight() / 2 == mapRT.GetHeight());
	assert(worldRect.GetWidth() / 2 == mapLB.GetWidth());
	assert(worldRect.GetHeight() / 2 == mapLB.GetHeight());
	assert(worldRect.GetWidth() / 2 == mapRB.GetWidth());
	assert(worldRect.GetHeight() / 2 == mapRB.GetHeight());
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

void World::RenderPrepare()
{
	camRenderX = int(cameraPos.x) - Graphics::gameWidth / 2;
	camRenderY = int(cameraPos.y) - Graphics::ScreenHeight / 2;
}

void World::RenderMap(Graphics& gfx, const RectI& DrawRect) const
{
	gfx.DrawSprite(left - camRenderX, top - camRenderY, DrawRect, mapLT, SpriteEffect::Copy{});
	gfx.DrawSprite(0 - camRenderX, top - camRenderY, DrawRect, mapRT, SpriteEffect::Copy{});
	gfx.DrawSprite(left - camRenderX, 0 - camRenderY, DrawRect, mapLB, SpriteEffect::Copy{});
	gfx.DrawSprite(0 - camRenderX, 0 - camRenderY, DrawRect, mapRB, SpriteEffect::Copy{});
}

void World::RenderText(Font& f, Graphics& gfx) const
{
	const std::string camPosStr = "Camera Pos:\n" + std::to_string(cameraPos.x) + '\n' + std::to_string(cameraPos.y);
	f.DrawText(camPosStr, { Graphics::ScreenWidth - Graphics::menuWidth + 8, 890 },
		Colors::LightGray, Graphics::GetMenuRect(), gfx);
}

void World::LoadMap(Surface& map, const std::string& map_in)
{
	map = Surface{ map_in };
}
