#pragma once

#include "Core.h"

namespace Crutch {

	class CHAPI Application 
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Client will define this
	Application* CreateApplication();
}

