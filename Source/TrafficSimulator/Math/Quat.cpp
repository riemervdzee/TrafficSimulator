/*
===============================================================================
Author: Mark van der Wal
Date: 28-08-2011
Description:
Quaternion implementation
reference[1]: 3D Math primer for graphics and game development.
===============================================================================
*/
#include "WildMath.h"

namespace wmath
{

	Quat::Quat()
	{
		this->w = 1.0f;
	}

	Quat::Quat(float w, float x, float y, float z)
	{
		this->vec.x = x;
		this->vec.y = y;
		this->vec.z = y;
		this->w = w;
	}

	Quat::Quat(const Vec3& axis, float angleDeg)
	{
		float halfTheta = DEG2RAD * angleDeg * 0.5f;
		float s = sinf(halfTheta);

		// set quaternion members
		this->w = cosf(halfTheta); 
		this->vec *= s;
	}

	Quat::Quat(const Mat3& mat)
	{
	}

	Quat::Quat(const Mat4& mat)
	{
	}

	Quat::Quat(float yawDeg, float pitchDeg, float rollDeg)
	{
		*this = Quat( Mat3::RotationEuler( yawDeg, pitchDeg, rollDeg ) );
	}

	float Quat::Length()
	{
		return static_cast<float>( sqrt( w * w + vec.x * vec.x + vec.y * vec.y + vec.z * vec.z ) );
	}

	void Quat::Normalize()
	{
		float m = 1.0f / Length();

		// normalize
		w *= m;
		vec *= m;
	}

	Quat Quat::Inverse()
	{
		float m = 1.0f / Length();
		return ~(*this) * m; // conjugate  * 1.0 / magnitude;
	}

	Quat Quat::operator*(const Quat& rhs)
	{
		return Quat();
	}

	Quat Quat::operator*(const float rhs)
	{
		return Quat();
	}

	Quat Quat::operator*(const Vec3& rhs)
	{
		return Quat();
	}

	Quat Quat::operator~() 
	{ 
		Quat temp;
		temp.w = w;
		temp.vec = -this->vec;
		return temp;
	}

	Mat3 Quat::ToMatrix3()
	{
		return Mat3();
	}

	Mat4 Quat::ToMatrix4()
	{
		return Mat4();
	}

	void Quat::ToAxisAngle(Vec3& vec, float& angleDeg)
	{
		angleDeg = static_cast<float>( 2 * acos( w ) * RAD2DEG );

		float m = Length();

		if( IsCloseEnough(m, 0.0f) )
			vec = this->vec;
		else
			vec = this->vec * (1.0f / m);
	}

	void Quat::ToEuler(float& yawDeg, float& pitchDeg, float& rollDeg)
	{
	}

	Quat Quat::Slerp(const Quat& a, const Quat& b, float t)
	{
		return Quat();
	}

	Quat operator*(const float lhs, const Quat& rhs)
	{
		return Quat();
	}

	Quat operator*(const Vec3& lhs, const Quat& rhs)
	{
		return Quat();
	}

} // namespace wmath