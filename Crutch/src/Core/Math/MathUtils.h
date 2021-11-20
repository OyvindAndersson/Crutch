#pragma once


namespace Crutch
{
	//--------------------------------------------------
	// Fwd decl.
	//--------------------------------------------------
	struct FVector2D;

	//--------------------------------------------------
	// Math constants
	//--------------------------------------------------
	#undef  PI
	#define PI				(3.1415926535897932f)
	#define EULERS_NUM		(2.71828182845904523536f)
	#define GOLDEN_RATIO	(1.6180339887498948482045868343656381f)
	#define SMALL_NUM		(1.e-8f)

	//--------------------------------------------------
	// Math utilities
	//--------------------------------------------------
	struct FMath
	{
		void CartesianToPolar( const FVector2D cart, FVector2D& outPolar );

		static inline float Pow( float fBase, float fExponent )
		{
			return powf( fBase, fExponent );
		}

		static inline float Sqrt( float fValue )
		{
			return std::sqrt( fValue );
		}

		static inline float InvSqrt( float fValue )
		{
			return 1.0f / std::sqrt( fValue );
		}
	};
}