#pragma once

#include "Font.h"
#include "Army.h"

class ArmyEditor
{
public:
	ArmyEditor(const std::string& background_in, Army& player_in);
	void Draw(Graphics& gfx, const RectI& drawRect, const Font& f) const;
private:
	Surface background;
	Army& player;
	Army temp = player;
};