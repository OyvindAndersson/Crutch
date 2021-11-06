#pragma once

#ifdef CH_PLATFORM_WINDOWS

/* 
	Will be defined in the Client app project
*/
extern Crutch::Application* Crutch::CreateApplication();

/* 
	Main entrypoint for windows platform 
*/
int main( int argc, char** argv ) {
	auto app = Crutch::CreateApplication();
	app->Run();
	delete app;
}

#endif