#pragma once
/*-------------------------------------------------------------------------------------------------
	[Crutch Engine]
	An excercise in building a 2D game on a *simple* custom engine. 
	
	Main goals
	- Learn how to create a clean application structure, easy to use by client project
	- Learn the basics of OpenGL (or more specifically, graphics programming)
	- Learn maths with code: purpously re-invent the wheel in some cases, to get to know the maths better
	  (even though perf could/will suffer)
	- Learn how to use third-party libraries and weld it into game objects (i.e: Box2D physics)
	- Learn more about data-structures and their applications more intuitively by doing a large project
	- Learn how to setup the build system so it can easily be shared without hiccups
	- Update c++ knowledge

	Resources
	- C++ and game engine: TheCherno: https:www.youtube.com/c/TheChernoProject
	- Tips/math: http:blog.wolfire.com/2009/07/linear-algebra-for-game-developers-part-1/
	- Tips/ref: Jonathan Blow Twitch stream - j_blow
	- SIMD/SOA: https://m.twitch.tv/videos/502748305
	

	Created by Øyvind Andersson - 07.11.2021

-------------------------------------------------------------------------------------------------*/

#include "Core/Application.h"
#include "Core/Log.h"
#include "Core/Entry.h"					/* ENTRY POINT */