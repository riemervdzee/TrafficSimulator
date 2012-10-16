/*
===============================================================================
Author: Mark van der Wal
Date: 28-08-2011
Description: Math library
===============================================================================
*/
#include "WildMath.h"

namespace wmath
{
	// Makes it easy to use the shortest arc when interpolating between two angles.
	// Reference[1]: 3D Math primer for graphics and game development.
	float WrapPI(float theta)
	{
		// Check if it is already in range
		if( fabs( theta ) <= PI)
		{
			// "Out of range" Determine how many "revolutions"
			// we need to add
			float revolutions = floorf( ( theta + PI ) * ( 1.0f / TWOPI ) );

			// subtract it off
			theta -= revolutions * TWOPI;
		}

		return theta;
	}

	// Let's use see if the value is close enough to some other value
	bool IsCloseEnough(float value, float near)
	{
		return fabsf( (value - near) / ( (near == 0.0f) ? 1.0f : near) ) < EPSILONS;
	}

	// Tells us if the passed in value is a power of 2
	bool IsPower2(int x)
	{
		return ( ( x > 0 ) && ( ( x & ( x - 1 ) ) == 0 ) );
	}

	// Gets us the next power of 2
	int NextPower2(int x)
	{
		int i = x & (~x + 1);

		while (i < x)
			i <<= 1;

		return i;
	}

	// Performs a linear interpolation
	template <typename T>
	T Lerp(const T &a, const T &b, float t)
	{
		return a + t * (b - a);
	}

	// performs smoothstep between 2 values
	float Smoothstep(float a, float b, float x)
	{
		if (x < a)
		{
			return 0.0f;
		}
		else if (x >= b)
		{
			return 1.0f;
		}
		else
		{
			x = (x - a) / (b - a);
			return x * x * (3.0f - 2.0f * x);
		}
	}
} // namespace wmath
