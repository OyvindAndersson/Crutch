#include "chpch.h"
#include "Application.h"
#include "WindowInterface.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Crutch {

	CApplication* CApplication::s_Instance = nullptr;

	//--------------------------------------------------
	// Generic definition of the application.
	//--------------------------------------------------

	CApplication::CApplication( const std::string& name )
	{
		CH_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

		m_window = IWindowInterface::Create();
		m_window->Initialize( FWindowDefinition( name ) );
		m_window->OnInputEvent.Bind<&CApplication::OnInputEvent>( *this );
		m_window->OnWindowEvent.Bind<&CApplication::OnWindowEvent>( *this );

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

		while ( m_bIsRunning )
		{
			m_window->Update();
		}
	}

	void CApplication::OnInputEvent( FInputEvent& event )
	{
		if ( event.InputType == EInputDeviceType::Keyboard )
		{
			FKeyEvent& keyEvent = (FKeyEvent&) event;
			CH_CORE_LOG( "Mouse input: {0}", keyEvent.Key );
		}
		else if ( event.InputType == EInputDeviceType::Mouse )
		{
			FMouseEvent& mouseEvent = (FMouseEvent&)event;
			CH_CORE_LOG( "Mouse input: {0}", mouseEvent.Button );
		}
	}

	void CApplication::OnWindowEvent( FWindowEvent& event )
	{
		if ( event.IsMaximizeEvent() )
		{
			CH_CORE_INFO( "Event Window Maximize: Was restored {0}", event.WasRestored() );
		}

	}

}