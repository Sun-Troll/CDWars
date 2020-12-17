#pragma once

#include "Graphics.h"
#include "Surface.h"
#include "Vec.h"

class Font
{
public:
	Font(const std::string& filename, Color chroma = Colors::White);
	void DrawText(const std::string& text, const VecI& pos, Color color, const RectI& clip, Graphics& gfx) const;
private:
	RectI MapGlyphRect(char c) const;
private:
	// holds the font sheet bitmap data
	Surface surface;
	// this gives the dimensions of a glyph in the font sheet
	int glyphWidth;
	int glyphHeight;
	// number of rows / columns in the font sheet (this is fixed)
	static constexpr int nColumns = 19;
	static constexpr int nRows = 5;
	// font sheet chroma color
	Color chroma;
	// start and end drawable character codes
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};