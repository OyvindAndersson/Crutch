#pragma once

#include "Core/Core.h"
#include "Application/Generic/WindowInterface.h"

int main( int argc, char** argv );

namespace Crutch 
{

	//--------------------------------------------------
	// Generic application that is responsible for
	// starting main loop and creating windows,
	// and register hardware input events
	//--------------------------------------------------
	class CApplication 
	{
	public:
		CApplication(const std::string& name);
		virtual ~CApplication();

		void Close();

	private:
		// Friend main runs the app
		void Run();

		void OnInputEvent( FInputEvent& event );
		void OnWindowEvent( FWindowEvent& event );

	public:
		IWindowInterface& GetWindow() { return *m_window; }
		static CApplication& Get() { return *s_Instance; }

	private:
		TUniquePtr<IWindowInterface> m_window;
		bool  m_bIsRunning     = true;
		bool  m_bIsMinimized   = false;
		float m_fLastFrameTime = 0.0f;

	private:
		static CApplication* s_Instance;
		friend int ::main( int argc, char** argv ); // see Core/Launch.h for definition
	};

	// Client will define this
	CApplication* CreateApplication();
}