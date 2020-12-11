#pragma once

#include "Vec.h"

template<typename T>
class Circ_
{
public:
	constexpr Circ_(const Vec_<T>& center_in, T radius_in)
		:
		center(center_in),
		radius(radius_in)
	{}
	bool Coliding(const Circ_<T>& circ) const
	{
		return (center - circ.center).GetLengthSq() < (radius + circ.radius) * (radius + circ.radius);
	}
	bool ContainsCirc(const Circ_<T>& circ) const
	{
		return (center - circ.center).GetLength() + circ.radius < radius;
	}
	bool ContainsPoint(const Vec_<T>& point) const
	{
		return (center - point).GetLengthSq() < radius * radius;
	}
public:
	Vec_<T> center;
	T radius;
};

typedef Circ_<float> CircF;
typedef Circ_<int> CircI;