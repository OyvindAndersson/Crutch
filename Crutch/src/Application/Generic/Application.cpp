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
		if ( event.IsKeyEvent() )
		{
			FKeyEvent& keyEvent = (FKeyEvent&)event;

			// TODO Push event to layers

			CH_CORE_LOG( "Event: {0}, Key name: {1}, Shift mod: {2}, Ctrl mod: {3}", 
						  keyEvent.GetKeyCode(), 
						  keyEvent.GetKey().GetName(), 
						  keyEvent.GetModifierKeys().IsShiftDown(),
						  keyEvent.GetModifierKeys().IsCtrlDown());
		}
		else if ( event.IsCursorEvent() )
		{
			FCursorEvent& cursorEvent = (FCursorEvent&) event;

			// TODO Push event to layers

			/*
			CH_CORE_INFO( "Key name: {0}, Pox X: {1}, Pos Y: {2}",
						  cursorEvent.GetKey().GetName(),
						  cursorEvent.GetPosX(),
						  cursorEvent.GetPosY());*/
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