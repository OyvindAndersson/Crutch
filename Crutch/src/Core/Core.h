#pragma once
/*
#ifdef CH_PLATFORM_WINDOWS
#ifdef CH_BUILD_DLL
#define  __declspec(dllexport)
#else
#define  __declspec(dllimport)
#endif
#else
	#error Crutch Engine only supports windows
#endif
*/

#include "Core/PlatformDetector.h"

#ifdef CH_DEBUG
	#if defined(CH_PLATFORM_WINDOWS)
		#define CH_DEBUGBREAK() __debugbreak()
	#elif defined(CH_PLATFORM_LINUX)
		#include <signal.h>
		#define CH_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define CH_ENABLE_ASSERTS
#else
	#define CH_DEBUGBREAK()
#endif

#define CH_EXPAND_MACRO(x) x
#define CH_STRINGIFY_MACRO(x) #x

#include "Events/Event.h"
#include "Core/Log.h"
#include "Core/Assert.h"