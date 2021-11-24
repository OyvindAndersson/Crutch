#pragma once

namespace Crutch
{
	struct FPlane
	{
		float X, Y, Z, W;

		FPlane()
			: X( 0.0f )
			, Y( 0.0f )
			, Z( 0.0f )
			, W( 0.0f )
		{}

		FPlane(float x, float y, float z, float w)
			: X( x )
			, Y( y )
			, Z( z )
			, W( w )
		{}
	};


	/*
	* 
	*  S* diagonal	= scaling a vector	   (downwards diagonal starting from the 1st element in the 1st column [0][0] -> [3][3])
	*  T* column	= translating a vector (top three values of the 4th column)
	* 
	* 
	*    Sx 0  0  Tx
	*	 0  Sy 0  Ty
	*	 0  0  Sz Tz
	*	 0  0  0  1
	* 
	*  Example: Translate a 3D unit vector up on the Z axis by 5, and along the X axis by 3 but don't change the scale
	*			We assume the 3D vector has been converted to a 4D, where the last element (w) is equal to '1'
	*  -------------------------------
	*    1  0  0  3  :(1 * x) + (0 * y) + (0 * z) + (3 * w) = (x + 0 + 0 + 3) = x + 3 = 4  |
	*    0  1  0  0  :(0 * x) + (1 * y) + (0 * z) + (0 * w) = (0 + y + 0 + 0) = y + 0 = 0  | 3D Vec
	*    0  0  1  5  :(0 * x) + (0 * y) + (1 * z) + (5 * w) = (0 + 0 + z + 5) = z + 5 = 6  |
	*    0  0  0  1  :(0 * x) + (0 * y) + (1 * z) + (1 * w) = (0 + 0 + 0 + 1) =     1 =(1)
	* 
	*  Example: Double the scale of a 3D vector, nothing else.
	*  -------------------------------
	*   2  0  0  0
	*   0  2  0  0
	*   0  0  2  0
	*   0  0  0  1
	* 
	* 
	* ----------------------------------------------------------------------------
	* Rotation transformation (Vector2D)
	* 
	* Lets call the transform "R2"  
	* 
	* [ cos(theta) -sin(theta) ]
	* [ sin(theta)  cos(theta) ]
	* 
	* Then we can rotate any 2D vector as such: R2 * vec2 = rotated vec2
	* 
	*/

	struct FMatrix
	{
		float M[4][4];

		FMatrix();
		FMatrix(const FPlane& x, const FPlane& y, const FPlane& z, const FPlane& w);

		FMatrix operator*( const FMatrix& other ) const;

		void SetScale( float fScale );

		const FPlane GetScale() const;
		static const FMatrix IdentityMatrix;

	};

	FMatrix::FMatrix()
	{

	}

	FMatrix::FMatrix( const FPlane& x, const FPlane& y, const FPlane& z, const FPlane& w )
	{
		M[0][0] = x.X; M[0][1] = x.Y; M[0][2] = x.Z; M[0][3] = x.W;
		M[1][0] = y.X; M[1][1] = y.Y; M[1][2] = y.Z; M[1][3] = y.W;
		M[2][0] = z.X; M[2][1] = z.Y; M[2][2] = z.Z; M[2][3] = z.W;
		M[3][0] = w.X; M[3][1] = w.Y; M[3][2] = w.Z; M[3][3] = w.W;
	}

	FMatrix FMatrix::operator*( const FMatrix& rhs ) const
	{
		FMatrix result;

		for ( int i = 0; i < 4; i++ )
		{
			for (int j = 0; j < 4; j++)
			{
				result.M[0][0] += M[i][j] * rhs.M[j][0];
				result.M[0][1] += M[i][j] * rhs.M[j][1];
			}
		}

		result.M[0][0] = M[0][0] * rhs.M[0][0] + M[0][1] * rhs.M[1][0] + M[0][2] * rhs.M[2][0] + M[0][3] * rhs.M[3][0];
		result.M[0][1] = M[0][0] * rhs.M[0][1] + M[0][1] * rhs.M[1][1] + M[0][2] * rhs.M[2][1] + M[0][3] * rhs.M[3][1];
		result.M[0][2] = M[0][0] * rhs.M[0][2] + M[0][1] * rhs.M[1][2] + M[0][2] * rhs.M[2][2] + M[0][3] * rhs.M[3][2];
		result.M[0][2] = M[0][0] * rhs.M[0][3] + M[0][1] * rhs.M[1][3] + M[0][2] * rhs.M[2][3] + M[0][3] * rhs.M[3][3];

		result.M[1][0] = M[1][0] * rhs.M[0][0] + M[1][1] * rhs.M[1][0] + M[1][2] * rhs.M[2][0] + M[1][3] * rhs.M[3][0];
		result.M[1][1] = M[1][0] * rhs.M[0][1] + M[1][1] * rhs.M[1][1] + M[1][2] * rhs.M[2][1] + M[1][3] * rhs.M[3][1];
		result.M[1][2] = M[1][0] * rhs.M[0][2] + M[1][1] * rhs.M[1][2] + M[1][2] * rhs.M[2][2] + M[1][3] * rhs.M[3][2];
		result.M[1][2] = M[1][0] * rhs.M[0][3] + M[1][1] * rhs.M[1][3] + M[1][2] * rhs.M[2][3] + M[1][3] * rhs.M[3][3];

		result.M[2][0] = M[2][0] * rhs.M[0][0] + M[2][1] * rhs.M[1][0] + M[2][2] * rhs.M[2][0] + M[2][3] * rhs.M[3][0];
		result.M[2][1] = M[2][0] * rhs.M[0][1] + M[2][1] * rhs.M[1][1] + M[2][2] * rhs.M[2][1] + M[2][3] * rhs.M[3][1];
		result.M[2][2] = M[2][0] * rhs.M[0][2] + M[2][1] * rhs.M[1][2] + M[2][2] * rhs.M[2][2] + M[2][3] * rhs.M[3][2];
		result.M[2][2] = M[2][0] * rhs.M[0][3] + M[2][1] * rhs.M[1][3] + M[2][2] * rhs.M[2][3] + M[2][3] * rhs.M[3][3];

		result.M[3][0] = M[3][0] * rhs.M[0][0] + M[3][1] * rhs.M[1][0] + M[3][2] * rhs.M[2][0] + M[3][3] * rhs.M[3][0];
		result.M[3][1] = M[3][0] * rhs.M[0][1] + M[3][1] * rhs.M[1][1] + M[3][2] * rhs.M[2][1] + M[3][3] * rhs.M[3][1];
		result.M[3][2] = M[3][0] * rhs.M[0][2] + M[3][1] * rhs.M[1][2] + M[3][2] * rhs.M[2][2] + M[3][3] * rhs.M[3][2];
		result.M[3][2] = M[3][0] * rhs.M[0][3] + M[3][1] * rhs.M[1][3] + M[3][2] * rhs.M[2][3] + M[3][3] * rhs.M[3][3];

		return result;
	}

	void FMatrix::SetScale( float fScale )
	{
		M[0][0] = M[1][1] = M[2][2] = M[3][3] = fScale;
	}

	const FPlane FMatrix::GetScale() const
	{
		return FPlane( M[0][0], M[1][1], M[2][2], M[3][3] );
	}

}