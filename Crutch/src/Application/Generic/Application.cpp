#include "chpch.h"
#include "Application.h"
#include "Window.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Crutch {

	//--------------------------------------------------
	// Generic definition of the application.
	// For now it depends on OpenGL.
	//--------------------------------------------------

	CApplication* CApplication::s_Instance = nullptr;

	CApplication::CApplication( const std::string& name )
	{
		CH_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

		m_window = IWindowInterface::Create( FWindowProperties( name ) );
		// m_window set event callback

		// Renderer init
	}
	
	CApplication::~CApplication()
	{
		// Renderer shutdown
	}

	void CApplication::Close()
	{
		m_bIsRunning = false;
	}

	void CApplication::Run()
	{
		CH_LOG("Application running");

		
	}

}