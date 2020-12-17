#include "Surface.h"

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pixels(width * height)
{}

Surface::Surface(Surface&& donor) noexcept
{
	*this = std::move(donor);
}

Surface& Surface::operator=(Surface&& rhs) noexcept
{
	width = rhs.width;
	height = rhs.height;
	pixels = std::move(rhs.pixels);
	rhs.width = 0;
	rhs.height = 0;
	return *this;
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

RectI Surface::GetRect() const
{
	return{ 0,width,0,height };
}

const Color* Surface::Data() const
{
	return pixels.data();
}