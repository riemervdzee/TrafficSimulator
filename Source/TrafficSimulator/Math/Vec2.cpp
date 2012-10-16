/*
===============================================================================
Author: Mark van der Wal
Date: 28-08-2011
Description: Vector2 implementation
===============================================================================
*/
#include "WildMath.h"

namespace wmath
{

// Addition operators
Vec2 Vec2::operator+(const Vec2& rhs) const
{
	Vec2 temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;;
	return temp;
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

// Subtraction operators
Vec2 Vec2::operator-(const Vec2& rhs) const
{
	Vec2 temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	return temp;
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

// scalar multiplication
Vec2 Vec2::operator*(float rhs)
{
	Vec2 temp;
	temp.x = x * rhs;
	temp.y = y * rhs;
	return temp;
}

Vec2& Vec2::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

// dot product
float Vec2::operator*(const Vec2& rhs)
{
	return x * rhs.x + y * rhs.y;
}

// negation operator
Vec2& Vec2::operator-()
{
	x = -x;
	y = -y;
	return *this;
}

// returns the length squared
float Vec2::LengthSq()
{
	return x*x + y*y;
}

// returns the length
float Vec2::Length()
{
	return sqrtf(x*x + y*y);
}

// normalize
float Vec2::Norm()
{
	float l = Length();
	x = x / l;
	y = y / l;
	return l;
}

} // namespace wmath