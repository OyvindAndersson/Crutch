#pragma once

#ifdef CH_PLATFORM_WINDOWS
#ifdef CH_BUILD_DLL
#define CHAPI __declspec(dllexport)
#else
#define CHAPI __declspec(dllimport)
#endif
#else
	#error Crutch Engine only supports windows
#endif
