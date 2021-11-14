#pragma once

#include "Core.h"

/*  Will be defined in the Client app project */
extern Crutch::CApplication* Crutch::CreateApplication();

/*  Main entrypoint for windows platform  */
int main( int argc, char** argv ) 
{
	// Call early subsystem initializers we might need before actual app start
	Crutch::CLog::Init();

	CH_CORE_INFO("Loggers initialized");

	auto app = Crutch::CreateApplication();

	app->Run();

	delete app;
}