#include "chpch.h"
#include "WindowInterface.h"

#ifdef CH_PLATFORM_WINDOWS
#include "Application/Windows/WindowsWindow.h"
#endif

namespace Crutch
{

	TUniquePtr<IWindowInterface> IWindowInterface::Create()
	{
#ifdef CH_PLATFORM_WINDOWS
		return MakeUnique<CWindowsWindow>();
#else
		CH_ASSERT( false, "Unknown platform!" );
		return nullptr;
#endif
	}

}