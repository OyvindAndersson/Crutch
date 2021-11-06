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

	// Client must define this
	Application* CreateApplication();
}

