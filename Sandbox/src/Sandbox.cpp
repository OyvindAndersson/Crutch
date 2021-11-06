/* Øyvind Andersson -  06.11.21 */

#include <Crutch.h>

class SandboxApp : public Crutch::Application {
public:
	SandboxApp() {

	}

	~SandboxApp() {

	}
};

Crutch::Application* Crutch::CreateApplication() {
	return new SandboxApp();
}