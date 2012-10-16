/*
===============================================================================
Author: Mark van der Wal
Date: 28-08-2011
Description: Vector3 implementation
===============================================================================
*/
#include "WildMath.h"

namespace wmath
{

// Addition operators
Vec3 Vec3::operator+(const Vec3& rhs) const
{
	Vec3 temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	temp.z = z + rhs.z;
	return temp;
}

Vec3& Vec3::operator+=(const Vec3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

// Subtraction operators
Vec3 Vec3::operator-(const Vec3& rhs) const
{
	Vec3 temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	temp.z = z - rhs.z;
	return temp;
}

Vec3& Vec3::operator-=(const Vec3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

// scalar multiplication
Vec3 Vec3::operator*(float rhs)
{
	Vec3 temp;
	temp.x = this->x * rhs;
	temp.y = this->y * rhs;
	temp.z = this->z * rhs;
	return temp;
}

Vec3& Vec3::operator*=(float rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;
	return *this;
}

// dot product
float Vec3::operator*(const Vec3& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

// negation operator
Vec3& Vec3::operator-()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

// returns the length squared
float Vec3::LengthSq()
{
	return x*x + y*y + z*z;
}

// returns the length
float Vec3::Length()
{
	return sqrtf(LengthSq());
}

// normalize
float Vec3::Norm()
{
	float l = Length();
	x = x / l;
	y = y / l;
	z = z / l;
	return l;
}

// cross two vectors!
Vec3 Vec3::Cross(const Vec3& rhs)
{
	Vec3 temp;
	temp.x = (y * rhs.z) - (z * rhs.y);
	temp.y = (z * rhs.x) - (x * rhs.z);
	temp.z = (x * rhs.y) - (y * rhs.x);
	return temp;
}

} // namespace wmath