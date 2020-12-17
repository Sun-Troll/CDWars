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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	f("Sprites\\Fonts\\asciitext.bmp"),
	world("Sprites\\Maps\\worldLT.bmp", "Sprites\\Maps\\worldRT.bmp",
		"Sprites\\Maps\\worldLB.bmp", "Sprites\\Maps\\worldRB.bmp")
{
	loadTime = "load time: " + std::to_string(stLoad.Duration());
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float ft = frameTimer.Duration();

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
}

void Game::ComposeFrame()
{
	world.RenderMap(gfx);
	world.RenderText(f, gfx);
	f.DrawText(loadTime, { 0, 0 }, Colors::Black, Graphics::GetScreenRect(), gfx);
}
