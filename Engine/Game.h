/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Menu.h"
#include "Stopwatch.h"
#include "ArmyEditor.h"
#include "SaveLoad.h"
#include "Battlefield.h"
#include <memory>

class Game
{
public:
	enum class Mode
	{
		Map,
		ArmyEdit,
		Battle
	};
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawPrepare();
	void DrawPartScreen(const RectI& screenPart);
	void DrawMenu();
	void DrawArmyEditor();
	void DrawFinish();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Stopwatch updateAndDrawWatch;
	float updateAndDrawTime = 0.0f;
	std::string loadTime;
	Stopwatch stLoad;
	Font font;
	std::random_device rd;
	std::mt19937 rngMain;
	Mode curMode = Mode::Map;
	World world;
	Menu menu;
	ArmyEditor armEdit;
	std::unique_ptr<Battlefield> bf;
	SaveLoad sL;
	Stopwatch frameTimer;
	/********************************/
};