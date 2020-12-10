#pragma once

#include <cmath>

template<typename T>
class Vec_
{
public:
	constexpr Vec_(T x_in, T y_in)
		:
		x(x_in),
		y(y_in)
	{}
	Vec_ operator+(const Vec_& rhs) const
	{
		return Vec_{ x + rhs.x, y + rhs.y };
	}
	Vec_& operator+=(const Vec_&rhs)
	{
		return *this = *this + rhs;
	}
	Vec_ operator-(const Vec_& rhs) const
	{
		return Vec_{ x - rhs.x, y - rhs.y };
	}
	Vec_& operator-=(const Vec_&rhs)
	{
		return *this = *this - rhs;
	}
	Vec_ operator*(const T rhs) const
	{
		return Vec_{ x * rhs, y * rhs };
	}
	Vec_ operator*=(const T rhs)
	{
		return *this = *this * rhs;
	}
	Vec_ operator/(const T rhs) const
	{
		return Vec_{ x / rhs, y / rhs };
	}
	Vec_ operator/=(const T rhs)
	{
		return *this = *this / rhs;
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	T GetLength() const
	{
		return std::sqrt(GetLengthSq());
	}
	Vec_ GetNormalized() const
	{
		const T length = GetLength();
		if (length != T(0))
		{
			return *this / length;
		}
		return *this;
	}
	Vec_& Normalize()
	{
		return *this = GetNormalized();
	}
	T GetDot(const Vec_& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}
private:
	T x;
	T y;
};

typedef Vec_<float> VecF;
typedef Vec_<int> VecI;
