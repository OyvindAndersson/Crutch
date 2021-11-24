#include "chpch.h"
#include "CrutchMath.h"

namespace Crutch
{

	//--------------------------------------------------
	// Globals
	//--------------------------------------------------

	const FVector2D FVector2D::ZeroVector( 0.0f, 0.0f );

	const FMatrix FMatrix::IdentityMatrix( FPlane( 1.0f, 0.0f, 0.0f, 0.0f ),
										   FPlane( 0.0f, 1.0f, 0.0f, 0.0f ),
										   FPlane( 0.0f, 0.0f, 1.0f, 0.0f ),
										   FPlane( 0.0f, 0.0f, 0.0f, 1.0f ) );

	//--------------------------------------------------
	// Other math helpers
	//--------------------------------------------------

	void FMath::CartesianToPolar( const FVector2D cart, FVector2D& outPolar )
	{

	}
}