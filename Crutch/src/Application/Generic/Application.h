#pragma once

#include "Core/Core.h"
#include "Window.h"

int main( int argc, char** argv );

namespace Crutch 
{

	class CApplication 
	{
	public:
		CApplication(const std::string& name);
		virtual ~CApplication();

		void Close();

		IWindowInterface& GetWindow() { return *m_window; }
		static CApplication& Get() { return *s_Instance; }

	private:
		void Run();

	private:
		TUniquePtr<IWindowInterface> m_window;
		bool  m_bIsRunning     = true;
		bool  m_bIsMinimized   = false;
		float m_fLastFrameTime = 0.0f;

	private:
		static CApplication* s_Instance;
		friend int ::main( int argc, char** argv ); // Only main is allowed to Run() the app.
	};

	// Client will define this
	CApplication* CreateApplication();
}