#include <Crutch.h>

class SandboxApp : public Crutch::CApplication 
{
public:
	SandboxApp() {}
	~SandboxApp() {}
};

/* Definition of the extern from Crutch engine */
Crutch::CApplication* Crutch::CreateApplication() 
{
	return new SandboxApp();
}