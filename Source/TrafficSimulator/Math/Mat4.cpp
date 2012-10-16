/*
===============================================================================
Author: Mark van der Wal
Date: 28-08-2011
Description: 4x4 Matrix implementation
===============================================================================
*/
#include "WildMath.h"

namespace wmath
{
	// constructor
	Mat4::Mat4()
	{
		// create identity
		m12 = m13 = m14 = 0.0f;
		m21 = m23 = m24 = 0.0f;
		m31 = m32 = m34 = 0.0f;
		m41 = m42 = m43 = 0.0f;
		m11 = m22 = m33 = m44 = 1.0f;
	}

	Mat4::Mat4(const Mat3& mat)
	{
		m11 = mat.m11; m21 = mat.m21; m31 = mat.m31; m41 = 0.0f;
		m12 = mat.m12; m22 = mat.m22; m32 = mat.m32; m42 = 0.0f;
		m13 = mat.m13; m23 = mat.m23; m33 = mat.m33; m43 = 0.0f;
		m14 = 0.0f; m24 = 0.0f; m34 = 0.0f; m44 = 1.0f;
	}

	//------------------------------------
	// (friend) Vector3 * Matrix multiplication
	//------------------------------------
	Vec3 operator*(const Vec3& rhs, const Mat4& lhs)
	{
		Vec3 temp;
		temp.x = rhs.x * lhs.m11 + rhs.y * lhs.m12 + rhs.z * lhs.m13 + lhs.m14;
		temp.y = rhs.x * lhs.m21 + rhs.y * lhs.m22 + rhs.z * lhs.m23 + lhs.m24;
		temp.z = rhs.x * lhs.m31 + rhs.y * lhs.m32 + rhs.z * lhs.m33 + lhs.m34;
		return temp;
	}

	// ###### OPERATOR OVERLOADING #########

	//------------------------------------
	// Matrix * Matrix multiplication
	//------------------------------------
	Mat4 Mat4::operator*(const Mat4& rhs) const
	{
		Mat4 temp;

		temp.m11 = m11 * rhs.m11 + m21 * rhs.m12 + m31 * rhs.m13 + m41 * rhs.m14; // row1 * column1 = newRow11
		temp.m21 = m11 * rhs.m21 + m21 * rhs.m22 + m31 * rhs.m23 + m41 * rhs.m24; // row1 * column2 = newRow21
		temp.m31 = m11 * rhs.m31 + m21 * rhs.m32 + m31 * rhs.m33 + m41 * rhs.m34; // row1 * column3 = newRow31
		temp.m41 = m11 * rhs.m41 + m21 * rhs.m42 + m31 * rhs.m43 + m41 * rhs.m44; // row1 * column4 = newRow41

		temp.m12 = m12 * rhs.m11 + m22 * rhs.m12 + m32 * rhs.m13 + m42 * rhs.m14; // row2 * column1 = newRow12
		temp.m22 = m12 * rhs.m21 + m22 * rhs.m22 + m32 * rhs.m23 + m42 * rhs.m24; // row2 * column2 = newRow22
		temp.m32 = m12 * rhs.m31 + m22 * rhs.m32 + m32 * rhs.m33 + m42 * rhs.m34; // row2 * column3 = newRow32
		temp.m42 = m12 * rhs.m41 + m22 * rhs.m42 + m32 * rhs.m43 + m42 * rhs.m44; // row2 * column4 = newRow42

		temp.m13 = m13 * rhs.m11 + m23 * rhs.m12 + m33 * rhs.m13 + m43 * rhs.m14; // row3 * column1 = newRow13
		temp.m23 = m13 * rhs.m21 + m23 * rhs.m22 + m33 * rhs.m23 + m43 * rhs.m24; // row3 * column2 = newRow23
		temp.m33 = m13 * rhs.m31 + m23 * rhs.m32 + m33 * rhs.m33 + m43 * rhs.m34; // row3 * column3 = newRow33
		temp.m43 = m13 * rhs.m41 + m23 * rhs.m42 + m33 * rhs.m43 + m43 * rhs.m44; // row3 * column4 = newRow43

		temp.m14 = m14 * rhs.m11 + m24 * rhs.m12 + m34 * rhs.m13 + m44 * rhs.m14; // row4 * column1 = newRow14
		temp.m24 = m14 * rhs.m21 + m24 * rhs.m22 + m34 * rhs.m23 + m44 * rhs.m24; // row4 * column2 = newRow24
		temp.m34 = m14 * rhs.m31 + m24 * rhs.m32 + m34 * rhs.m33 + m44 * rhs.m34; // row4 * column3 = newRow34
		temp.m44 = m14 * rhs.m41 + m24 * rhs.m42 + m34 * rhs.m43 + m44 * rhs.m44; // row4 * column4 = newRow44

		return temp;
	}

	//------------------------------------
	// Matrix * Vector3 multiplication
	//------------------------------------
	Vec3 Mat4::operator*(const Vec3& rhs)
	{
		Vec3 temp;
		temp.x = m11 * rhs.x + m21 * rhs.y + m31 * rhs.z + m41; // row 1 * column1
		temp.y = m12 * rhs.x + m22 * rhs.y + m32 * rhs.z + m42; // row 2 * column2
		temp.z = m13 * rhs.x + m23 * rhs.y + m33 * rhs.z + m43; // row 3 * column3
		return temp;
	}

	//--------------------------------------
	// Get Euler rotation angles in degrees
	// reference[1]: 3D Math primer for graphics and game development p.280-281.
	//--------------------------------------
	void Mat4::GetEuler(float& yaw, float& pitch, float& roll)
	{
		// checking for domain errors
		float sp = -m32;
		if( sp <= -1.0f )
		{
			pitch  = -1.570796f * RAD2DEG; // -pi/2
		}
		else if ( sp >= 1.0f)
		{
			pitch  = 1.570796f * RAD2DEG; // pi/2
		}
		else
		{
			pitch = asinf(sp) ;
		}

		// chek for gimbal lock case
		if( IsCloseEnough( fabs(sp), 1.0f ) )
		{
			// in this case we are looking straight up or down
			yaw = atan2f(-m13, m11);
			roll = 0.0f;
		}
		else // no gimbal lock
		{
			// compute yaw
			yaw = atan2f(m31, m33) * RAD2DEG;

			// compute roll
			roll = atan2f(m12, m22) * RAD2DEG;
		}
	}

	//------------------------------------
	// Transposing the matrix
	//------------------------------------
	Mat4 Mat4::Transpose()
	{
		// cpoy over
		Mat4 temp = *this;

		// row to column 1
		temp.m12 = temp.m21;
		temp.m13 = temp.m31;
		temp.m14 = temp.m41;

		// row to column 2
		temp.m21 = temp.m12;
		temp.m23 = temp.m32;
		temp.m24 = temp.m42;

		// row to column 3
		temp.m31 = temp.m13;
		temp.m32 = temp.m23;
		temp.m34 = temp.m43;

		// row to column 4
		temp.m41 = temp.m14;
		temp.m42 = temp.m24;
		temp.m43 = temp.m34;

		return temp;
	}

	//------------------------------------
	// Returns the determinant of the matrix
	//------------------------------------
	float Mat4::Det()
	{
		return (m11 * m22 - m21 * m12)
			* (m33 * m44 - m43 * m34)
			- (m11 * m32 - m31 * m12)
			* (m23 * m44 - m43 * m24)
			+ (m11 * m42 - m41 * m12)
			* (m23 * m34 - m33 * m24)
			+ (m21 * m32 - m31 * m22)
			* (m13 * m44 - m43 * m14)
			- (m21 * m42 - m41 * m22)
			* (m13 * m34 - m33 * m14)
			+ (m31 * m42 - m41 * m32)
			* (m13 * m24 - m23 * m14);
	}

	//------------------------------------
	// Returns the determinant of the matrix
	//------------------------------------
	Mat4 Mat4::Invert()
	{
		Mat4 temp;

		// get the determinant
		float d = Det();

		// if det is close enough to 0
		if( IsCloseEnough(d, 0.0f) )
			return temp;

		d = 1.0f / d;

		// get inverted matrix by multiplying the adjoint by 1.0f / determinant
		temp.m11 = d * (m22 * (m33 * m44 - m43 * m34) + m32 * (m43 * m24 - m23 * m44) + m42 * (m23 * m34 - m33 * m24));
		temp.m21 = d * (m23 * (m31 * m44 - m41 * m34) + m33 * (m41 * m24 - m21 * m44) + m43 * (m21 * m34 - m31 * m24));
		temp.m31 = d * (m24 * (m31 * m42 - m41 * m32) + m34 * (m41 * m22 - m21 * m42) + m44 * (m21 * m32 - m31 * m22));
		temp.m41 = d * (m21 * (m42 * m33 - m32 * m43) + m31 * (m22 * m43 - m42 * m23) + m41 * (m32 * m23 - m22 * m33));

		temp.m12 = d * (m32 * (m13 * m44 - m43 * m14) + m42 * (m33 * m14 - m13 * m34) + m12 * (m43 * m34 - m33 * m44));
		temp.m22 = d * (m33 * (m11 * m44 - m41 * m14) + m43 * (m31 * m14 - m11 * m34) + m13 * (m41 * m34 - m31 * m44));
		temp.m32 = d * (m34 * (m11 * m42 - m41 * m12) + m44 * (m31 * m12 - m11 * m32) + m14 * (m41 * m32 - m31 * m42));
		temp.m42 = d * (m31 * (m42 * m13 - m12 * m43) + m41 * (m12 * m33 - m32 * m13) + m11 * (m32 * m43 - m42 * m33));

		temp.m13 = d * (m42 * (m13 * m24 - m23 * m14) + m12 * (m23 * m44 - m43 * m24) + m22 * (m43 * m14 - m13 * m44));
		temp.m23 = d * (m43 * (m11 * m24 - m21 * m14) + m13 * (m21 * m44 - m41 * m24) + m23 * (m41 * m14 - m11 * m44));
		temp.m33 = d * (m44 * (m11 * m22 - m21 * m12) + m14 * (m21 * m42 - m41 * m22) + m24 * (m41 * m12 - m11 * m42));
		temp.m43 = d * (m41 * (m22 * m13 - m12 * m23) + m11 * (m42 * m23 - m22 * m43) + m21 * (m12 * m43 - m42 * m13));

		temp.m14 = d * (m12 * (m33 * m24 - m23 * m34) + m22 * (m13 * m34 - m33 * m14) + m32 * (m23 * m14 - m13 * m24));
		temp.m24 = d * (m13 * (m31 * m24 - m21 * m34) + m23 * (m11 * m34 - m31 * m14) + m33 * (m21 * m14 - m11 * m24));
		temp.m34 = d * (m14 * (m31 * m22 - m21 * m32) + m24 * (m11 * m32 - m31 * m12) + m34 * (m21 * m12 - m11 * m22));
		temp.m44 = d * (m11 * (m22 * m33 - m32 * m23) + m21 * (m32 * m13 - m12 * m33) + m31 * (m12 * m23 - m22 * m13));

		return temp;
	}

	// ####### STATIC METHODS ###############

	//--------------------------------------
	// Create a translation matrix
	//--------------------------------------
	Mat4 Mat4::Translate(const Vec3& vec)
	{
		Mat4 temp;
		temp.m41 = vec.x;
		temp.m42 = vec.y;
		temp.m43 = vec.z;

		return temp;
	}

	//--------------------------------------
	// Create a translation matrix
	//--------------------------------------
	Mat4 Mat4::Translate(float x, float y, float z)
	{
		Mat4 temp;
		temp.m41 = x;
		temp.m42 = y;
		temp.m43 = z;

		return temp;
	}

	//--------------------------------------
	// Create a scale matrix around a axis
	//--------------------------------------
	Mat4 Mat4::ScaleUniform(float v)
	{
		Mat4 temp;
		temp.m11 = v;
		temp.m22 = v;
		temp.m33 = v;
		return temp;
	}

	//--------------------------------------
	// Create a scale matrix around a arbitary axis
	// reference[1]: 3D Math primer for graphics and game development
	//--------------------------------------
	Mat4 Mat4::ScaleAxis(float x, float y, float z, float scale)
	{
		Mat4 temp;

		// first column
		temp.m11 = 1 + (scale - 1) * x * x;
		temp.m12 = (scale - 1) * x * y;
		temp.m13 = (scale - 1) * x * z;

		// second column
		temp.m21 = (scale - 1) * x * y;
		temp.m22 = 1 + (scale - 1) * y * y;
		temp.m23 = (scale - 1) * y * z;

		// third column
		temp.m31 = (scale - 1) * x * z;
		temp.m32 = (scale - 1) * y * z;
		temp.m33 = 1 + (scale - 1) * z * z;

		return temp;
	}

	//--------------------------------------
	// Create a rotation matrix around an arbitary axis
	//--------------------------------------
	Mat4 Mat4::RotationAxis(Vec3 axis, float angle)
	{
		return RotationAxis(axis.x, axis.y, axis.z, angle);
	}

	//--------------------------------------
	// Create a rotation matrix around an arbitary axis
	// reference[1]: 3D Math primer for graphics and game development
	//--------------------------------------
	Mat4 Mat4::RotationAxis(float x, float y, float z, float angle)
	{
		Mat4 temp;
		float cos = cosf( angle * DEG2RAD );
		float sin = sinf( angle * DEG2RAD );

		temp.m11 = x * x * (1.0f - cos) + cos;
		temp.m12 = x * y * (1.0f - cos) + z * sin;
		temp.m13 = x * z * (1.0f - cos) - y * sin;

		temp.m21 = y * x * (1.0f - cos) - z * sin;
		temp.m22 = y * y * (1.0f - cos) + cos;
		temp.m23 = y * z * (1.0f - cos) + x * sin;

		temp.m31 = z * x * (1.0f - cos) + y * sin;
		temp.m32 = z * y * (1.0f - cos) - x * sin;
		temp.m33 = z * z * (1.0f - cos) + cos;

		return temp;
	}

	//--------------------------------------
	// Create a rotation matrix around the world X axis
	//--------------------------------------
	Mat4 Mat4::RotationX(float angle)
	{
		Mat4 temp;
		float cos = cosf( angle * DEG2RAD );
		float sin = sinf( angle * DEG2RAD );

		temp.m22 = cos;
		temp.m23 = sin;
		temp.m32 = -sin;
		temp.m33 = cos;

		return temp;
	}

	//--------------------------------------
	// Create a rotation matrix around the world Y axis
	//--------------------------------------
	Mat4 Mat4::RotationY(float angle)
	{
		Mat4 temp;
		float cos = cosf( angle * DEG2RAD );
		float sin = sinf( angle * DEG2RAD );

		temp.m11 = cos;
		temp.m13 = -sin;
		temp.m31 = sin;
		temp.m33 = cos;

		return temp;
	}

	//--------------------------------------
	// Create a rotation matrix around the world Z axis
	//--------------------------------------
	Mat4 Mat4::RotationZ(float angle)
	{
		Mat4 temp;
		float cos = cosf( angle * DEG2RAD );
		float sin = sinf( angle * DEG2RAD );

		temp.m11 = cos;
		temp.m12 = sin;
		temp.m21 = -sin;
		temp.m22 = cos;

		return temp;
	}

	//--------------------------------------
	// Create a rotation matrix based on the euler angles
	// reference[1]: 3D Math primer for graphics and game development
	//--------------------------------------
	Mat4 Mat4::RotationEuler(float yaw, float pitch, float roll)
	{
		return Mat4::RotationY(yaw) *
			Mat4::RotationX(pitch) *
			Mat4::RotationZ(roll);
	}

	//-------------------------------------------------
	// create a perspective projection matrix
	//-------------------------------------------------
	Mat4 Mat4::CreatePerspective(float fov, float aspect, float n, float f)
	{
		Mat4 temp;
		float tan = 1 / tanf( (fov / 2) * DEG2RAD );

		temp.m11 = tan;
		temp.m22 = tan * aspect;
		temp.m33 = (f + n) / (f - n);
		temp.m43 = (-2 * n * f) / (f - n);
		temp.m34 = 1;
		return temp;
	}

	//-------------------------------------------------
	// create a orthographic matrix projection matrix
	//-------------------------------------------------
	Mat4 Mat4::CreateOrthographic(float l, float r, float t, float b, float n, float f)
	{
		Mat4 temp;

		temp.m11 = 2.0f / (r - l);
		temp.m22 = 2.0f / (t - b);
		temp.m33 = 2.0f / (f - n);

		temp.m41 = -(r + l) / (r - l);
		temp.m42 = -(t + b) / (t - b);
		temp.m43 = -(f + n) / (f - n);

		return temp;
	}

	//-------------------------------------------------
	// create a orthographic2D projection matrix
	// this is for openGL as opengl's convention is bottom up for screen coordinates
	//-------------------------------------------------
	Mat4 Mat4::CreateOrthographic2D(int width, int height, float n, float f)
	{
		return CreateOrthographic(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, n, f);
	}

	//############## HELPER METHODS ########### TODO WILL BE MOVED TO TRANSFORM CLASS

	void Mat4::SetRight(float x, float y, float z)
	{
		m11 = x;
		m12 = y;
		m13 = z;
	}

	void Mat4::SetRight(Vec3 v)
	{
		SetRight(v.x, v.y, v.z);
	}

	void Mat4::SetUp(float x, float y, float z)
	{
		m21 = x;
		m22 = y;
		m23 = z;
	}

	Vec3 Mat4::GetRight()
	{
		return Vec3(m11, m12, m13);
	}

	void Mat4::SetUp(Vec3 v)
	{
		SetUp(v.x, v.y, v.z);
	}

	Vec3 Mat4::GetUp()
	{
		return Vec3(m21, m22, m23);
	}

	void Mat4::SetForward(float x, float y, float z)
	{
		m31 = x;
		m32 = y;
		m33 = z;
	}

	void Mat4::SetForward(Vec3 v)
	{
		SetForward(v.x, v.y, v.z);
	}

	Vec3 Mat4::GetForward()
	{
		return Vec3(m31, m32, m33);
	}

	void Mat4::SetPosition(float x, float y, float z)
	{
		m41 = x;
		m42 = y;
		m43 = z;
	}

	void Mat4::SetPosition(Vec3 v)
	{
		SetPosition(v.x, v.y, v.z);
	}

	Vec3 Mat4::GetPosition()
	{
		return Vec3(m41, m42, m43);
	}

} // namespace wmath
