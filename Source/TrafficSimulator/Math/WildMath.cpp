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
        /// <summary>Normalizes a value in a wraparound numeric range</summary> 
        /// <param name="value">Value to be normalized</param> 
        /// <param name="lower">Lower wraparound point (inclusive)</param> 
        /// <param name="upper">Upper wraparound point (exclusive)</param> 
        /// <returns>The normalized input value</returns> 
        float Wrap(float value, float lower, float upper) 
        { 
            float distance = upper - lower; 
            float times = (float)floorf((value - lower) / distance); 

            return value - (times * distance); 
        }
    
        /// <summary> 
        ///   Calculates the smallest angle between two absolute directions 
        /// </summary> 
        /// <param name="firstPhi">First absolute direction in radians</param> 
        /// <param name="secondPhi">Second absolute direction in radians</param> 
        /// <returns>The smallest angle between both directions</returns> 
        float ShortestAngleBetween(float firstPhi, float secondPhi) 
        { 
            float difference = secondPhi - firstPhi; 

            // Just unroll the difference of both angles and we have the angle 
            float angle = Wrap(difference, 0.0f, TWOPI); 

            // Go the other way around if we got the longer path 
            if(angle >= PI) 
              angle -= TWOPI; 

            return angle; 
        } 
    
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
