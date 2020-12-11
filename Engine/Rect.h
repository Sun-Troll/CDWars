#pragma once

#include "Vec.h"

template<typename T>
class Rect_
{
public:
	constexpr Rect_(T left_in, T right_in, T top_in, T bottom_in)
		:
		left(left_in),
		right(right_in),
		top(top_in),
		bottom(bottom_in)
	{}
	Rect_(const Vec_<T>& leftTop, const Vec_<T>& rightBottom)
		:
		Rect_(leftTop.x, rightBottom.x, leftTop.y, rightBottom.y)
	{}
	Rect_(const Vec_<T>& leftTop, T width, T height)
		:
		Rect_(leftTop.x, leftTop.x + width, leftTop.y, leftTop.y + height)
	{}
	bool Overlaps(const Rect_<T>& rhs) const
	{
		return left < rhs.right && right > rhs.left && top < rhs.bottom && bottom > rhs.top;
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}
public:
	T left;
	T right;
	T top;
	T bottom;
};

typedef Rect_<float> RectF;
typedef Rect_<int> RectI;