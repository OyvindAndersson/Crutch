#pragma once

#include "Core.h"

namespace Crutch {

	class CHAPI CApplication 
	{
	public:
		CApplication();
		virtual ~CApplication();

		void Run();
	};

	// Client will define this
	CApplication* CreateApplication();
}