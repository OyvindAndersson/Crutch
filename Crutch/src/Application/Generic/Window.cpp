#include "chpch.h"
#include "Window.h"

#ifdef CH_PLATFORM_WINDOWS
#include "Application/Windows/WindowsWindow.h"
#endif

namespace Crutch
{

	FWindowProperties FWindowProperties::Default = FWindowProperties( "Crutch Engine", 1280, 720 );

	TUniquePtr<IWindowInterface> IWindowInterface::Create( const FWindowProperties& properties /* = FWindowProperties() */ )
	{
#ifdef CH_PLATFORM_WINDOWS
		return MakeUnique<CWindowsWindow>( properties );
#else
		CH_ASSERT( false, "Unknown platform!" );
		return nullptr;
#endif
	}

}