#pragma once

#ifdef CH_PLATFORM_WINDOWS

#include "Core.h"

/*  Will be defined in the Client app project */
extern Crutch::Application* Crutch::CreateApplication();


/*  Main entrypoint for windows platform  */
int main( int argc, char** argv ) 
{
	// Call early subsystem initializers we might need before actual app start
	Crutch::Log::Init();

	CH_CORE_WARN("Loggers initialized");

	auto app = Crutch::CreateApplication();
	app->Run();
	delete app;
}

#endif