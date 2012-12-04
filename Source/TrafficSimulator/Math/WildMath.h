/*
===============================================================================
Author: Mark van der Wal
Date: 28-08-2011
Description: Math library

TODO: 
- Quaternion class is not done! DONT USE!
- Mat3 & Mat4 require testing
===============================================================================
*/
#ifndef _WILDMATH_H_
#define _WILDMATH_H_

#include <cmath>

namespace wmath
{

// global math constants
const float PI = 3.141592f;
const float TWOPI = PI * 2.0f;
const float PIOVERTWO = PI / 2.0f;
const float DEG2RAD = PI / 180.f;
const float RAD2DEG = 180.0f / PI;
const float EPSILONS = 1e-6f;
const float EPSILONH = 1e-3f;

float Wrap(float value, float lower, float upper);
float ShortestAngleBetween(float firstPhi, float secondPhi);

//------------------------------------
// makes it easy to use the shortest arc when interpolating between two angles.
// reference[1]: 3D Math primer for graphics and game development.
//---------------------------------
float WrapPI(float theta);

//------------------------------------
// let's use see if the value is close enough to some other value
//------------------------------------
bool IsCloseEnough(float value, float near);

//------------------------------------
// power of 2 functions
//------------------------------------
bool IsPower2(int x);
int NextPower2(int x);

//------------------------------------
// performs a linear interpolation
//------------------------------------
template <typename T>
T Lerp(const T &a, const T &b, float t);

//------------------------------------
// performs a smoothstep between 2 values
//------------------------------------
float Smoothstep(float a, float b, float x);

//-------------------------------------------------------------------------
// 2D vector class
//-------------------------------------------------------------------------
class Vec2
{
public:
	// constructors
	Vec2() : x(0.0f), y(0.0f) {}
	Vec2(float px, float py) 
		: x(px), y(py) {}

	//------------------------------------
	// Addition operators
	//------------------------------------
	Vec2 operator+(const Vec2& rhs) const;
	Vec2& operator+=(const Vec2& rhs);

	//------------------------------------
	// Subtraction operators
	//------------------------------------
	Vec2 operator-(const Vec2& rhs) const;
	Vec2& operator-=(const Vec2& rhs);

	//------------------------------------
	// scalar multiplication
	//------------------------------------
	Vec2 operator*(float rhs);
	Vec2& operator*=(float rhs);

	//------------------------------------
	// Dot product
	//------------------------------------
	float operator*(const Vec2& rhs);

	//------------------------------------
	// negates this vector
	//------------------------------------
	Vec2& operator-();

	//------------------------------------
	// returns the length squared of this vector
	//------------------------------------
	float LengthSq();

	//------------------------------------
	// returns the length of this vector
	//------------------------------------
	float Length();

	//------------------------------------
	// normalize
	//------------------------------------
	float Norm();

public:
	float x, y;
};

//-------------------------------------------------------------------------
// 3D vector class
//-------------------------------------------------------------------------
class Vec3
{
public:
	// constructors
	Vec3(): x(0.0f), y(0.0f), z(0.0f) {}
	Vec3(float px, float py, float pz)
		: x(px), y(py), z(pz) {}
	Vec3(const Vec3& v) { *this = v;}

	void operator=(const Vec3& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	//------------------------------------
	// vector addition
	//------------------------------------
	Vec3 operator+(const Vec3& rhs) const;
	Vec3& operator+=(const Vec3& rhs);

	//------------------------------------
	// vector subtraction
	//------------------------------------
	Vec3 operator-(const Vec3& rhs) const;
	Vec3& operator-=(const Vec3& rhs);

	//------------------------------------
	// scalar multiplication
	//------------------------------------
	Vec3 operator*(float rhs);
	Vec3& operator*=(float rhs);

	//------------------------------------
	// dot product this vector by rhs vector
	//------------------------------------
	float operator*(const Vec3& rhs);

	//------------------------------------
	// negate this vector
	//------------------------------------
	Vec3& operator-();

	//------------------------------------
	// returns the length squared of this vector
	//------------------------------------
	float LengthSq();

	//------------------------------------
	// returns the length of this vector
	//------------------------------------
	float Length();

	//------------------------------------
	// normalize this vector
	//------------------------------------
	float Norm();

	//------------------------------------
	// cross product this vector by rhs vector
	//------------------------------------
	Vec3 Cross(const Vec3& rhs);

public:
	float x, y, z;
};

//-------------------------------------------------------------------------
// 3 x 3 column matrix
//-------------------------------------------------------------------------
class Mat4;
class Mat3
{
public:
	Mat3();
	Mat3(const Mat4& mat);

	// ###### OPERATOR OVERLOADING #########

	//------------------------------------
	// Matrix * Matrix multiplication
	//------------------------------------
	Mat3 operator*(const Mat3& rhs) const;

	//------------------------------------
	// Matrix * Vector multiplication
	//------------------------------------
	Vec3 operator*(const Vec3& rhs);

	//------------------------------------
	// Vector3 * Matrix multiplication
	//------------------------------------
	friend Vec3 operator*(const Vec3& rhs, const Mat3& lhs);

	//--------------------------------------
	// Get Euler rotation angles in degrees
	//--------------------------------------
	void GetEuler(float& yaw, float& pitch, float& roll);

	//------------------------------------
	// Transposing the matrix
	//------------------------------------
	Mat3 Transpose();

	//------------------------------------
	// Returns the determinant of the matrix
	//------------------------------------
	float Det();

	//------------------------------------
	// Returns the determinant of the matrix
	//------------------------------------
	Mat3 Invert();

	// ####### STATIC METHODS ###############
	//--------------------------------------
	// Create a scale matrix around a axis
	//--------------------------------------
	static Mat3 ScaleUniform(float v);

	//--------------------------------------
	// Create a scale matrix around a arbitary axis
	//--------------------------------------
	static Mat3 ScaleAxis(float x, float y, float z, float scale);

	//--------------------------------------
	// Create a rotation matrix around an arbitary axis
	//--------------------------------------
	static Mat3 RotationAxis(Vec3 axis, float angle);

	//--------------------------------------
	// Create a rotation matrix around an arbitary axis
	//--------------------------------------
	static Mat3 RotationAxis(float x, float y, float z, float angle);

	//--------------------------------------
	// Create a rotation matrix around the world X axis
	//--------------------------------------
	static Mat3 RotationX(float angle);

	//--------------------------------------
	// Create a rotation matrix around the world Y axis
	//--------------------------------------
	static Mat3 RotationY(float angle);

	//--------------------------------------
	// Create a rotation matrix around the world Z axis
	//--------------------------------------
	static Mat3 RotationZ(float angle);

	//--------------------------------------
	// Create a rotation matrix based on the euler angles
	//--------------------------------------
	static Mat3 RotationEuler(float yaw, float pitch, float roll);

public:
	float	m11, m12, m13, // column 1
			m21, m22, m23, // column 2
			m31, m32, m33; // column 3
};

//-------------------------------------------------------------------------
// 4 x 4 column matrix
//-------------------------------------------------------------------------
class Mat4
{
public:
	// constructor
	Mat4();
	Mat4(const Mat3& mat);

	// ###### OPERATOR OVERLOADING #########

	//------------------------------------
	// Matrix * Matrix multiplication
	//------------------------------------
	Mat4 operator*(const Mat4& rhs) const;

	//------------------------------------
	// Matrix * Vector multiplication
	//------------------------------------
	Vec3 operator*(const Vec3& rhs);

	//------------------------------------
	// Vector3 * Matrix multiplication
	//------------------------------------
	friend Vec3 operator*(const Vec3& rhs, const Mat4& lhs);

	//--------------------------------------
	// Get Euler rotation angles in degrees
	//--------------------------------------
	void GetEuler(float& yaw, float& pitch, float& roll);

	//------------------------------------
	// Transposing the matrix
	//------------------------------------
	Mat4 Transpose();

	//------------------------------------
	// Returns the determinant of the matrix
	//------------------------------------
	float Det();

	//------------------------------------
	// Returns the determinant of the matrix
	//------------------------------------
	Mat4 Invert();

	// ####### STATIC METHODS ###############
	//--------------------------------------
	// Create a translation matrix
	//--------------------------------------
	static Mat4 Translate(const Vec3& vec);

	//--------------------------------------
	// Create a translation matrix
	//--------------------------------------
	static Mat4 Translate(float x, float y, float z);

	//--------------------------------------
	// Create a scale matrix around a axis
	//--------------------------------------
	static Mat4 ScaleUniform(float v);

	//--------------------------------------
	// Create a scale matrix around a arbitary axis
	//--------------------------------------
	static Mat4 ScaleAxis(float x, float y, float z, float scale);

	//--------------------------------------
	// Create a rotation matrix around an arbitary axis
	//--------------------------------------
	static Mat4 RotationAxis(Vec3 axis, float angle);

	//--------------------------------------
	// Create a rotation matrix around an arbitary axis
	//--------------------------------------
	static Mat4 RotationAxis(float x, float y, float z, float angle);

	//--------------------------------------
	// Create a rotation matrix around the world X axis
	//--------------------------------------
	static Mat4 RotationX(float angle);

	//--------------------------------------
	// Create a rotation matrix around the world Y axis
	//--------------------------------------
	static Mat4 RotationY(float angle);

	//--------------------------------------
	// Create a rotation matrix around the world Z axis
	//--------------------------------------
	static Mat4 RotationZ(float angle);

	//--------------------------------------
	// Create a rotation matrix based on the euler angles
	//--------------------------------------
	static Mat4 RotationEuler(float yaw, float pitch, float roll);

	//-------------------------------------------------
	// create a perspective projection matrix
	//-------------------------------------------------
	static Mat4 CreatePerspective(float fov, float aspect, float n, float f);

	//-------------------------------------------------
	// create a orthographic matrix projection matrix
	//-------------------------------------------------
	static Mat4 CreateOrthographic(float l, float r, float t, float b, float n, float f);

	//-------------------------------------------------
	// create a orthographic2D projection matrix
	// this is for openGL as OpenGL's convention is bottom up for screen coordinates
	//-------------------------------------------------
	static Mat4 CreateOrthographic2D(int width, int height, float n, float f);

	//############# HELPER METHODS ########### TODO: NEEDS TO BE MOVED TO TRANSFORM CLASS
	void SetRight(float x, float y, float z);
	void SetRight(Vec3 v);
	Vec3 GetRight();

	void SetUp(float x, float y, float z);
	void SetUp(Vec3 v);
	Vec3 GetUp();

	void SetForward(float x, float y, float z);
	void SetForward(Vec3 v);
	Vec3 GetForward();

	void SetPosition(float x, float y, float z);
	void SetPosition(Vec3 v);
	Vec3 GetPosition();

public:
	float	m11, m12, m13, m14, // column 1
			m21, m22, m23, m24, // column 2
			m31, m32, m33, m34, // column 3
			m41, m42, m43, m44; // column 4
};

//-------------------------------------------------------------------------
// Quaternion
// reference[1]: 3D Math primer for graphics and game development.
//-------------------------------------------------------------------------
class Quat
{
public:
	//------------------------------------
	// constructors
	//------------------------------------
	Quat();
	Quat(float w, float x, float y, float z);
	Quat(const Vec3& axis, float angleDeg);
	Quat(const Mat3& mat);
	Quat(const Mat4& mat);
	Quat(float yawDeg, float pitchDeg, float rollDeg);

	//------------------------------------
	// Utility
	//------------------------------------
	float Length();
	void  Normalize();
	Quat  Inverse();

	//------------------------------------
	// Operator overloading
	//------------------------------------
	Quat operator*(const Quat& rhs);
	Quat operator*(const float rhs);
	friend Quat operator*(const float lhs, const Quat& rhs);
	Quat operator*(const Vec3& rhs);
	friend Quat operator*(const Vec3& lhs, const Quat& rhs);
	Quat operator~(); // conjugate

	//------------------------------------
	// To orientation representation
	//------------------------------------
	Mat3 ToMatrix3();
	Mat4 ToMatrix4();
	void ToAxisAngle(Vec3& vec, float& angleDeg);
	void ToEuler(float& yawDeg, float& pitchDeg, float& rollDeg);

	//------------------------------------
	// SLERP
	// Both quaternions must be unit length and represent absolute rotations.
	//------------------------------------
	static Quat Slerp(const Quat& a, const Quat& b, float t);

private:
	Vec3  vec;
	float w;
};

} // namespace wmath

#endif