#pragma once

#include "Vec.h"

template<typename T>
class LineSeg_
{
public:
	LineSeg_(const Vec_<T>& beg_in, const Vec_<T>& end_in)
		:
		beg(beg_in),
		end(end_in)
	{}
	LineSeg_(const Vec_<T>& beg_in, const Vec_<T>& dir, T length)
		:
		beg(beg_in),
		end(beg + dir * length)
	{}
	Vec_<T> GetVec() const
	{
		return end - beg;
	}
public:
	const Vec_<T> beg;
	Vec_<T> end;
};

typedef LineSeg_<float> LineSegF;
typedef LineSeg_<int> LineSegI;