#define GOD_GRAPHICS
#include "Graphics.h"

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