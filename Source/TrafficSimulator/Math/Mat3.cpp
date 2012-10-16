#include "WildMath.h"

namespace wmath
{

// constructor
Mat3::Mat3()
{
	// create identity
	m12 = m13 = 0.0f;
	m21 = m23 = 0.0f;
	m31 = m32 = 0.0f;
	m11 = m22 = m33 = 1.0f;
}

Mat3::Mat3(const Mat4& mat)
{
	m11 = mat.m11; m21 = mat.m21; m31 = mat.m31;
	m12 = mat.m12; m22 = mat.m22; m32 = mat.m32;
	m13 = mat.m13; m23 = mat.m23; m33 = mat.m33;
}

//------------------------------------
// (friend) Vector3 * Matrix multiplication
//------------------------------------
Vec3 operator*(const Vec3& rhs, const Mat3& lhs)
{
	Vec3 temp;
	temp.x = rhs.x * lhs.m11 + rhs.y * lhs.m12 + rhs.z * lhs.m13;
	temp.y = rhs.x * lhs.m21 + rhs.y * lhs.m22 + rhs.z * lhs.m23;
	temp.z = rhs.x * lhs.m31 + rhs.y * lhs.m32 + rhs.z * lhs.m33;
	return temp;
}

// ###### OPERATOR OVERLOADING #########

//------------------------------------
// Matrix * Matrix multiplication
//------------------------------------
Mat3 Mat3::operator*(const Mat3& rhs) const
{
	Mat3 temp;

	temp.m11 = m11 * rhs.m11 + m21 * rhs.m12 + m31 * rhs.m13; // row1 * column1 = newRow11
	temp.m21 = m11 * rhs.m21 + m21 * rhs.m22 + m31 * rhs.m23; // row1 * column2 = newRow21
	temp.m31 = m11 * rhs.m31 + m21 * rhs.m32 + m31 * rhs.m33; // row1 * column3 = newRow31

	temp.m12 = m12 * rhs.m11 + m22 * rhs.m12 + m32 * rhs.m13; // row2 * column1 = newRow12
	temp.m22 = m12 * rhs.m21 + m22 * rhs.m22 + m32 * rhs.m23; // row2 * column2 = newRow22
	temp.m32 = m12 * rhs.m31 + m22 * rhs.m32 + m32 * rhs.m33; // row2 * column3 = newRow32

	temp.m13 = m13 * rhs.m11 + m23 * rhs.m12 + m33 * rhs.m13; // row3 * column1 = newRow13
	temp.m23 = m13 * rhs.m21 + m23 * rhs.m22 + m33 * rhs.m23; // row3 * column2 = newRow23
	temp.m33 = m13 * rhs.m31 + m23 * rhs.m32 + m33 * rhs.m33; // row3 * column3 = newRow33

	return temp;
}

//------------------------------------
// Matrix * Vector3 multiplication
//------------------------------------
Vec3 Mat3::operator*(const Vec3& rhs)
{
	Vec3 temp;
	temp.x = m11 * rhs.x + m21 * rhs.y + m31 * rhs.z; // row 1 * column1 (vector3)
	temp.y = m12 * rhs.x + m22 * rhs.y + m32 * rhs.z; // row 2 * column1 (vector3)
	temp.z = m13 * rhs.x + m23 * rhs.y + m33 * rhs.z; // row 3 * column1 (vector3)
	return temp;
}

//--------------------------------------
// Get Euler rotation angles in degrees
// reference[1]: 3D Math primer for graphics and game development p.280-281.
//--------------------------------------
void Mat3::GetEuler(float& yaw, float& pitch, float& roll)
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
Mat3 Mat3::Transpose()
{
	// cpoy over
	Mat3 temp = *this;

	// row to column 1
	temp.m12 = temp.m21;
	temp.m13 = temp.m31;

	// row to column 2
	temp.m21 = temp.m12;
	temp.m23 = temp.m32;

	// row to column 3
	temp.m31 = temp.m13;
	temp.m32 = temp.m23;

	return temp;
}

//------------------------------------
// Returns the determinant of the matrix
//------------------------------------
float Mat3::Det()
{
	return m11 * m22 * m33 -
			m11 * m32 * m23 +
			m21 * m12 * m33 -
			m21 * m13 * m32 +
			m31 * m12 * m23 -
			m31 * m13 * m22;
}

//------------------------------------
// Returns the determinant of the matrix
//------------------------------------
Mat3 Mat3::Invert()
{
	Mat3 temp;

	// get the determinant
	float d = Det();

	// if det is close enough to 0
	if( IsCloseEnough(d, 0.0f) )
		return temp;

	d = 1.0f / d;

	// calculate inverted matrix
	temp.m11 = (m22*m33 - m23*m32) * d;
	temp.m21 = -(m12*m33 - m13*m32) * d;
	temp.m31 = (m12*m23 - m13*m22) * d;

	temp.m12 = -(m21*m33 - m23*m31) * d;
	temp.m22 = (m11*m33 - m13*m31) * d;
	temp.m23 = -(m11*m23 - m13*m21) * d;

	temp.m31 = (m12*m23 - m13*m22) * d;
	temp.m32 = -(m11*m23 - m13*m21) * d;
	temp.m33 = (m11*m22 - m12*m21) * d;

	return temp;
}

//--------------------------------------
// Create a scale matrix around a axis
//--------------------------------------
Mat3 Mat3::ScaleUniform(float v)
{
	Mat3 temp;
	temp.m11 = v;
	temp.m22 = v;
	temp.m33 = v;
	return temp;
}

//--------------------------------------
// Create a scale matrix around a arbitary axis
// reference[1]: 3D Math primer for graphics and game development
//--------------------------------------
Mat3 Mat3::ScaleAxis(float x, float y, float z, float scale)
{
	Mat3 temp;

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
Mat3 Mat3::RotationAxis(Vec3 axis, float angle)
{
	return RotationAxis(axis.x, axis.y, axis.z, angle);
}

//--------------------------------------
// Create a rotation matrix around an arbitary axis
// reference[1]: 3D Math primer for graphics and game development
//--------------------------------------
Mat3 Mat3::RotationAxis(float x, float y, float z, float angle)
{
	Mat3 temp;
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
Mat3 Mat3::RotationX(float angle)
{
	Mat3 temp;
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
Mat3 Mat3::RotationY(float angle)
{
	Mat3 temp;
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
Mat3 Mat3::RotationZ(float angle)
{
	Mat3 temp;
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
Mat3 Mat3::RotationEuler(float yaw, float pitch, float roll)
{
	return Mat3::RotationY(yaw) *
		Mat3::RotationX(pitch) *
		Mat3::RotationZ(roll);
}

} // namespace wmath
