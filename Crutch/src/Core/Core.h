#pragma once
#include <memory.h>

#ifdef CH_PLATFORM_WINDOWS
#ifdef CH_BUILD_DLL
#define CHAPI __declspec(dllexport)
#else
#define CHAPI __declspec(dllimport)
#endif
#else
	#error Crutch Engine only supports windows
#endif

#include <GLFW/glfw3.h>
#include "Events/Event.h"
#include "Log.h"