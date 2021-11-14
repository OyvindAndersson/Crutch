#pragma once

#include <Core/PlatformDetector.h>

#ifdef CH_PLATFORM_WINDOWS
	#ifndef NOMINMAX
	// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <memory>

#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <type_traits>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <Core/Memory/Pointers.h>

#ifdef CH_PLATFORM_WINDOWS
	#include <Windows.h>
#endif