/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <thread>
#include <functional>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	font("Sprites\\Fonts\\asciitext.bmp"),
	rngMain(rd()),
	world("Sprites\\Maps\\worldLT.bmp", "Sprites\\Maps\\worldRT.bmp",
		"Sprites\\Maps\\worldLB.bmp", "Sprites\\Maps\\worldRB.bmp",
		"Sprites\\Armies\\armyPlayer.bmp", "Sprites\\Armies\\armyEnemy.bmp",
		"Sprites\\Armies\\armyTarget.bmp"),
	menu("Sprites\\Menu\\menuBackground.bmp", "Sprites\\Maps\\wMinimap.bmp"),
	armEdit("Sprites\\ArmyEditor\\armyBackground.bmp", world.SetPlayer())
{
	loadTime = "load time: " + std::to_string(stLoad.Duration());
}

void Game::Go()
{
	gfx.BeginFrame();
	updateAndDrawWatch.Duration();
	std::thread t0(&Game::DrawMenu, std::ref(*this));
	//DrawMenu();
	DrawPrepare();
	std::thread t1(&Game::DrawPartScreen, std::ref(*this), Graphics::GetGameLTRect());
	std::thread t2(&Game::DrawPartScreen, std::ref(*this), Graphics::GetGameRTRect());
	std::thread t3(&Game::DrawPartScreen, std::ref(*this), Graphics::GetGameLBRect());
	std::thread t4(&Game::DrawPartScreen, std::ref(*this), Graphics::GetGameRBRect());
	//DrawPartScreen(Graphics::GetGameRect());
	t0.join();
	UpdateModel();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	DrawFinish();
	ComposeFrame();
	updateAndDrawTime = updateAndDrawWatch.Duration() * 1000.0f;
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float ft = frameTimer.Duration();

	if (curMode == Mode::Map)
	{
		world.SpawnEnemies(rngMain);

		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;

		if (wnd.kbd.KeyIsPressed('A'))
		{
			left = true;
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			right = true;
		}
		if (wnd.kbd.KeyIsPressed('W'))
		{
			up = true;
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			down = true;
		}

		world.MoveCamera(left, right, up, down, ft);

		Army::State state = Army::State::March;

		while (!wnd.kbd.KeyIsEmpty())
		{
			const Keyboard::Event e = wnd.kbd.ReadKey();
			if (e.IsRelease())
			{
				if (e.GetCode() == '1' || e.GetCode() == '2' || e.GetCode() == '3')
				{
					if (e.GetCode() == '2')
					{
						state = Army::State::Scout;
					}
					else if (e.GetCode() == '3')
					{
						state = Army::State::Sneak;
					}
					world.PlayerSetState(state);
				}
			}
		}

		if (wnd.mouse.LeftIsPressed())
		{
			const VecF mousePos = wnd.mouse.GetPos();
			if (mousePos.x < float(Graphics::gameWidth))
			{
				world.PlayerSetTarget(mousePos);
			}
			else
			{
				menu.SetWorldCamPos(world, mousePos);
				menu.ChangeSelect(VecI(mousePos));
			}
		}

		world.ClampCamera();

		world.EnemiesSetTarget(rngMain);
		world.ArmiesMove(ft);
	}
}

void Game::DrawPrepare()
{
	if (curMode == Mode::Map)
	{
		world.DrawPrepare();
	}
}

void Game::DrawPartScreen(const RectI& screenPart)
{
	if (curMode == Mode::Map)
	{
		world.DrawMap(gfx, screenPart);
		world.DrawArmies(gfx, screenPart);
	}
}

void Game::DrawMenu()
{
	menu.DrawWorld(gfx, Graphics::GetMenuRect(), font, world);
}

void Game::DrawArmyEditor()
{
	if (curMode == Mode::ArmyEdit)
	{
		armEdit.Draw(gfx, Graphics::GetGameRect(), font);
	}
}

void Game::DrawFinish()
{
	if (curMode == Mode::Map)
	{
		world.DrawHeading(gfx);
		world.DrawDetect(gfx);
	}
}

void Game::ComposeFrame()
{
	font.DrawText(loadTime, { 0, 0 }, Colors::Black, Graphics::GetScreenRect(), gfx);
	font.DrawText("frame time ms: " + std::to_string(updateAndDrawTime), { 0, 40 }, Colors::Black, Graphics::GetScreenRect(), gfx);
}
