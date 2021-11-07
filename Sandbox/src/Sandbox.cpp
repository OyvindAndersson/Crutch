#include <Crutch.h>

class SandboxApp : public Crutch::Application 
{
public:
	SandboxApp() 
	{

	}

	~SandboxApp() 
	{

	}
};

/* Definition of the extern from Crutch engine */
Crutch::Application* Crutch::CreateApplication() 
{
	return new SandboxApp();
}