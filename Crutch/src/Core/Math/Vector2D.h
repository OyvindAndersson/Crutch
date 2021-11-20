#pragma once

namespace Crutch
{
	//--------------------------------------------------
	// Vector with two components
	//--------------------------------------------------
	struct FVector2D
	{
		float X;
		float Y;

		/** Zero vector constant, global */
		static const FVector2D ZeroVector;

		inline FVector2D();
		explicit inline FVector2D( float fValue );
		explicit inline FVector2D( float x, float y );
		inline FVector2D( const FVector2D& other );

	/** Operators */
	public:
		inline FVector2D operator+( const FVector2D& other ) const;
		inline FVector2D operator-( const FVector2D& other ) const;
		inline FVector2D operator*( const FVector2D& other ) const;
		FVector2D operator/( const FVector2D& other ) const;

		inline FVector2D operator+( float fValue ) const;
		inline FVector2D operator-( float fValue ) const;
		inline FVector2D operator*( float fScale ) const;
		FVector2D operator/( float fScale ) const;

		inline FVector2D operator+=( const FVector2D& other );
		inline FVector2D operator-=( const FVector2D& other );
		inline FVector2D operator*=( const FVector2D& other );
		FVector2D operator/=( const FVector2D& other );

		inline FVector2D operator*=( float fScale );
		FVector2D operator/=( float fValue );
		
		bool operator==( const FVector2D& other ) const;
		bool operator!=( const FVector2D& other ) const;
		bool operator<( const FVector2D& other ) const;
		bool operator>( const FVector2D& other ) const;
		bool operator<=( const FVector2D& other ) const;
		bool operator>=( const FVector2D& other ) const;

		// Inverse
		FVector2D operator-() const;

	/** Other arithmetic */
	public:
		/**
		 * Gets the dot product of *this vector and the input vector
		 * @param other The second vector
		 * @returns The dot product
		 */
		float Dot( const FVector2D& other ) const;

		/**
		 * Gets the dot product between two vectors
		 * @param vecA The first vector
		 * @param vecB The second vector
		 * @returns The dot product
		 */
		inline static float Dot( const FVector2D& vecA, const FVector2D& vecB );

		/**
		 * Gets the cross product of *this vector and the input vector
		 * @param other The second vector
		 * @returns The cross product
		 */
		float Cross( const FVector2D& other ) const;

		/**
		 * Gets the cross product between two vectors
		 * @param vecA The first vector
		 * @param vecB The second vector
		 * @returns The cross product
		 */
		inline static float Cross( const FVector2D& vecA, const FVector2D& vecB );

		/**
		 * Calculates the length/magnitude of this vector
		 */
		float Length() const;

		/**
		 * Normalizes the vector, or zeroes it if the squared sum is too small
		 */
		void Normalize();

		/**
		 * Normalizes a vector, or zeroes it if the squared sum is too small
		 * @param vec The vector to normalize
		 * @returns The normalized vector
		 */
		inline static FVector2D Normalize( const FVector2D& vec );
	};

	//--------------------------------------------------
	// Inline functions
	//--------------------------------------------------

	FVector2D::FVector2D()
		: X(0.0f), Y(0.0f)
	{}

	FVector2D::FVector2D( float fValue )
		: X(fValue), Y(fValue)
	{}

	FVector2D::FVector2D( float x, float y )
		: X( x ), Y( y )
	{}

	FVector2D::FVector2D( const FVector2D& other )
		: X( other.X ), Y( other.Y )
	{}

	FVector2D FVector2D::operator-() const
	{
		return FVector2D( -X, -Y );
	}

	FVector2D operator*( float fScale, const FVector2D& vec )
	{
		return vec.operator*( fScale );
	}

	FVector2D FVector2D::operator+( const FVector2D& other ) const
	{
		return FVector2D( X + other.X, Y + other.Y );
	}

	FVector2D FVector2D::operator+( float fValue ) const
	{
		return FVector2D( X + fValue, Y + fValue );
	}

	FVector2D FVector2D::operator-( const FVector2D& other ) const
	{
		return FVector2D( X - other.X, Y - other.Y );
	}

	FVector2D FVector2D::operator-( float fValue ) const
	{
		return FVector2D( X - fValue, Y - fValue );
	}

	FVector2D FVector2D::operator*( const FVector2D& other ) const
	{
		return FVector2D( X * other.X, Y * other.Y );
	}

	FVector2D FVector2D::operator*( float fScale ) const
	{
		return FVector2D( X * fScale, Y * fScale );
	}

	FVector2D FVector2D::operator/( const FVector2D& other ) const
	{
		return FVector2D( X / other.X, Y / other.Y );
	}

	FVector2D FVector2D::operator/( float fScale ) const
	{
		const float ratio = 1.0f / fScale;
		return FVector2D( X * ratio, Y * ratio );
	}

	FVector2D FVector2D::operator/=( const FVector2D& other )
	{
		X /= other.X;
		Y /= other.Y;
		return *this;
	}

	FVector2D FVector2D::operator/=( float fValue )
	{
		const float ratio = 1.0f / fValue;
		X *= ratio;
		Y *= ratio;
		return *this;
	}

	bool FVector2D::operator<( const FVector2D& other ) const
	{
		return ( X < other.X && Y < other.Y );
	}

	bool FVector2D::operator>( const FVector2D& other ) const
	{
		return ( X > other.X && Y > other.Y );
	}

	bool FVector2D::operator>=( const FVector2D& other ) const
	{
		return ( X >= other.X && Y >= other.Y );
	}

	bool FVector2D::operator<=( const FVector2D& other ) const
	{
		return ( X <= other.X && Y <= other.Y );
	}

	bool FVector2D::operator!=( const FVector2D& other ) const
	{
		return ( X != other.X && Y != other.Y );
	}

	bool FVector2D::operator==( const FVector2D& other ) const
	{
		return ( X == other.X && Y == other.Y );
	}

	FVector2D FVector2D::operator*=( float fScale )
	{
		X *= fScale;
		Y *= fScale;
		return *this;
	}

	FVector2D FVector2D::operator*=( const FVector2D& other )
	{
		X *= other.X;
		Y *= other.Y;
		return *this;
	}

	FVector2D FVector2D::operator-=( const FVector2D& other )
	{
		X -= other.X;
		Y -= other.Y;
		return *this;
	}

	FVector2D FVector2D::operator+=( const FVector2D& other )
	{
		X += other.X;
		Y += other.Y;
		return *this;
	}

	float FVector2D::Dot( const FVector2D& other ) const
	{
		return X * other.X + Y * other.Y;
	}

	float FVector2D::Dot( const FVector2D& vecA, const FVector2D& vecB )
	{
		return vecA.X * vecB.X + vecA.Y * vecB.Y;
	}

	float FVector2D::Cross( const FVector2D& other ) const
	{
		return X * other.Y - Y * other.X;
	}

	float FVector2D::Cross( const FVector2D& vecA, const FVector2D& vecB )
	{
		return vecA.X * vecB.Y - vecA.Y * vecB.X;
	}

	float FVector2D::Length() const
	{
		return sqrt( X * X + Y * Y );
	}

	void FVector2D::Normalize()
	{
		float squaredSum = X * X + Y * Y;
		if ( squaredSum > SMALL_NUM )
		{
			float scale = FMath::InvSqrt( squaredSum );
			X *= scale;
			Y *= scale;
		}
		else
		{
			X = 0.0f;
			Y = 0.0f;
		}
	}

	FVector2D FVector2D::Normalize( const FVector2D& vec )
	{
		float squaredSum = vec.X * vec.X + vec.Y * vec.Y;
		if ( squaredSum > SMALL_NUM )
		{
			float scale = FMath::InvSqrt( squaredSum );
			return FVector2D( vec.X * scale, vec.Y * scale );
		}
		else
		{
			return FVector2D::ZeroVector;
		}
	}

}