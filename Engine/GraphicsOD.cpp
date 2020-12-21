#define GOD_GRAPHICS
#include "Graphics.h"
#include <algorithm>

void Graphics::BeginFrame()
{
	// clear the sysbuffer
	memset(pSysBuffer, 0u, sizeof(Color) * Graphics::ScreenHeight * Graphics::ScreenWidth);
}

void Graphics::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < int(Graphics::ScreenWidth));
	assert(y >= 0);
	assert(y < int(Graphics::ScreenHeight));
	pSysBuffer[Graphics::ScreenWidth * y + x] = c;
}

void Graphics::DrawRect(const RectI& rect, Color c)
{
	assert(rect.left < rect.right);
	assert(rect.top < rect.bottom);
	assert(rect.left >= 0);
	assert(rect.right <= ScreenWidth);
	assert(rect.top >= 0);
	assert(rect.bottom <= ScreenHeight);
	const int bottom = rect.bottom - 1;
	for (int x = rect.left; x < rect.right; ++x)
	{
		PutPixel(x, rect.top, c);
		PutPixel(x, bottom, c);
	}
	const int right = rect.right - 1;
	for (int y = rect.top + 1; y < rect.bottom - 1; ++y)
	{
		PutPixel(rect.left, y, c);
		PutPixel(right, y, c);
	}
}

void Graphics::DrawCirc(const CircI& circ, Color c)
{
	assert(circ.radius > 0);
	const int left = circ.center.x - circ.radius + 1;
	const int right = circ.center.x + circ.radius - 1;
	const int top = circ.center.y - circ.radius + 1;
	const int bottom = circ.center.y + circ.radius - 1;
	if (left < ScreenWidth && right >= 0 && top < ScreenHeight && bottom >= 0)
	{
		if (circ.center.y >= 0 && circ.center.y < ScreenHeight)
		{
			if (left >= 0)
			{
				PutPixel(left, circ.center.y, c);
			}
			if (right < ScreenWidth)
			{
				PutPixel(right, circ.center.y, c);
			}
		}
		if (circ.center.x >= 0 && circ.center.x < ScreenWidth)
		{
			if (top >= 0)
			{
				PutPixel(circ.center.x, top, c);
			}
			if (bottom < ScreenHeight)
			{
				PutPixel(circ.center.x, bottom, c);
			}
		}
		const int radSq = circ.radius * circ.radius;
		const int stop = int(std::sqrt(radSq / 2));
		for (int x = 1; x <= stop; ++x)
		{
			const int y = int(std::sqrt(radSq - x * x));
			const int left = circ.center.x - x;
			const int right = circ.center.x + x;
			const int top = circ.center.y - y;
			const int bottom = circ.center.y + y;
			if (left >= 0 && left < ScreenWidth)
			{
				if (top >= 0 && top < ScreenHeight)
				{
					PutPixel(left, top, c);
				}
				if (bottom >= 0 && bottom < ScreenHeight)
				{
					PutPixel(left, bottom, c);
				}
			}
			if (right >= 0 && right < ScreenWidth)
			{
				if (top >= 0 && top < ScreenHeight)
				{
					PutPixel(right, top, c);
				}
				if (bottom >= 0 && bottom < ScreenHeight)
				{
					PutPixel(right, bottom, c);
				}
			}
		}
		for (int y = 1; y <= stop; ++y)
		{
			const int x = int(std::sqrt(radSq - y * y));
			const int left = circ.center.x - x;
			const int right = circ.center.x + x;
			const int top = circ.center.y - y;
			const int bottom = circ.center.y + y;
			if (left >= 0 && left < ScreenWidth)
			{
				if (top >= 0 && top < ScreenHeight)
				{
					PutPixel(left, top, c);
				}
				if (bottom >= 0 && bottom < ScreenHeight)
				{
					PutPixel(left, bottom, c);
				}
			}
			if (right >= 0 && right < ScreenWidth)
			{
				if (top >= 0 && top < ScreenHeight)
				{
					PutPixel(right, top, c);
				}
				if (bottom >= 0 && bottom < ScreenHeight)
				{
					PutPixel(right, bottom, c);
				}
			}
		}
	}
}

void Graphics::DrawLine(VecF v0, VecF v1, Color c)
{
	if (std::max(v0.x, v1.x) >= 0 && std::min(v0.x, v1.x) < gameWidth
		&& std::max(v0.y, v1.y) >= 0 && std::min(v0.y, v1.y) < ScreenHeight)
	{
		if (v0.y == v1.y)
		{
			if (v0.x > v1.x)
			{
				std::swap(v0, v1);
			}
			const float stop = std::min(v1.x, float(gameWidth));
			for (float x = std::max(std::floor(v0.x), 0.0f); x < stop; ++x)
			{
				PutPixel(int(x), int(v0.y), c);
			}
		}

		else if (v0.x == v1.x)
		{
			if (v0.y > v1.y)
			{
				std::swap(v0, v1);
			}
			const float stop = std::min(v1.y, float(ScreenHeight));
			for (float y = std::max(std::floor(v0.y), 0.0f); y < stop; ++y)
			{
				PutPixel(int(v0.x), int(y), c);
			}
		}

		else
		{
			const float run = v1.x - v0.x;
			const float rise = v1.y - v0.y;

			if (std::abs(run) > std::abs(rise))
			{
				if (v0.x > v1.x)
				{
					std::swap(v0, v1);
				}

				const float m = rise / run;
				const float b = v0.y - v0.x * m;

				const float stop = std::min(v1.x, float(gameWidth));
				for (float x = std::max(std::floor(v0.x), 0.0f); x < stop; ++x)
				{
					const int y = int(x * m + b);
					if (y >= 0 && y < ScreenHeight)
					{
						PutPixel(int(x), y, c);
					}
				}
			}
			else
			{
				if (v0.y > v1.y)
				{
					std::swap(v0, v1);
				}

				const float mr = run / rise;
				const float br = v0.x - v0.y * mr;

				const float stop = std::min(v1.y, float(ScreenHeight));
				for (float y = std::max(std::floor(v0.y), 0.0f); y < stop; ++y)
				{
					const int x = int(y * mr + br);
					if (x >= 0 && x < gameWidth)
					{
						PutPixel(x, int(y), c);
					}
				}
			}
		}
	}
}

void Graphics::DrawCross(const VecI& pos, int size, Color c)
{
	for (int x = pos.x - size; x < pos.x; ++x)
	{
		PutPixel(x, pos.y, c);
	}
	for (int x = pos.x + size; x > pos.x; --x)
	{
		PutPixel(x, pos.y, c);
	}
	for (int y = pos.y - size; y < pos.y; ++y)
	{
		PutPixel(pos.x, y, c);
	}
	for (int y = pos.y + size; y > pos.y; --y)
	{
		PutPixel(pos.x, y, c);
	}
}

Color Graphics::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < int(Graphics::ScreenWidth));
	assert(y >= 0);
	assert(y < int(Graphics::ScreenHeight));
	return pSysBuffer[Graphics::ScreenWidth * y + x];
}

void dummy(Graphics& gfx)
{
	gfx.DrawSprite(0, 0, RectI{ 0,0,0,0 }, RectI{ 0,0,0,0 }, Surface{}, SpriteEffect::Copy{});
	gfx.DrawSprite(0, 0, RectI{ 0,0,0,0 }, RectI{ 0,0,0,0 }, Surface{}, SpriteEffect::Chroma{ Colors::Black });
	gfx.DrawSprite(0, 0, RectI{ 0,0,0,0 }, RectI{ 0,0,0,0 }, Surface{}, SpriteEffect::Substitution{ Colors::Black,Colors::Black });
}