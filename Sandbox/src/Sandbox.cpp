#include <Crutch.h>

class SandboxApp : public Crutch::CApplication 
{
public:
	SandboxApp( const std::string& name ) : CApplication( name ){}
	~SandboxApp() {}
};

/* Definition of the extern from Crutch engine */
Crutch::CApplication* Crutch::CreateApplication() 
{
	return new SandboxApp("Sandbox");
}