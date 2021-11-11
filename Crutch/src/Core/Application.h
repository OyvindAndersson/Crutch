#pragma once

#include "Core.h"

namespace Crutch {

	class CApplication 
	{
	public:
		CApplication();
		virtual ~CApplication();

		void Run();
	};

	// Client will define this
	CApplication* CreateApplication();
}