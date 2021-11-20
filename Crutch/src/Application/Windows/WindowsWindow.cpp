#include "chpch.h"
#include "WindowsWindow.h"
#include "Application/Generic/Application.h"

#include "Core/Input.h"
#include "Events/Events.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Crutch
{

	CWindowsWindow::CWindowsWindow()
	{
		m_pWindow = nullptr;
	}
	CWindowsWindow::~CWindowsWindow()
	{
		Shutdown();
	}

	void CWindowsWindow::Initialize( CApplication* const application, const FWindowDefinition& definition )
	{
		m_windowDefinition = definition;

		glfwInit();

#ifdef CH_DEBUG
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		//glfwWindowHint( GLFW_RESIZABLE, GL_TRUE );
#endif

		m_pWindow = glfwCreateWindow( m_windowDefinition.Width, m_windowDefinition.Height, m_windowDefinition.Title.c_str(), nullptr, nullptr );
		if ( !m_pWindow )
		{
			CH_CORE_ERROR( "Failed to create GLFW window!" );
			glfwTerminate();
			exit( 1 );
		}

		glfwMakeContextCurrent( m_pWindow );

		//------------------------------------
		// Set callbacks

		glfwSetWindowUserPointer( m_pWindow,  this );

		glfwSetKeyCallback( m_pWindow, []( GLFWwindow* window, int key, int scancode, int action, int mods ) {

			CWindowsWindow* self = (CWindowsWindow*) glfwGetWindowUserPointer( window );
			CH_CORE_ASSERT( self , "Native window was nullptr, which should never happen here.");

			FModifierKeysState modState( ( mods & GLFW_MOD_SHIFT ) != 0, ( mods & GLFW_MOD_SHIFT ) != 0,
										 ( mods & GLFW_MOD_CONTROL ) != 0, ( mods & GLFW_MOD_CONTROL ) != 0,
										 ( mods & GLFW_MOD_ALT ) != 0, ( mods & GLFW_MOD_ALT ) != 0,
										 ( mods & GLFW_MOD_CAPS_LOCK ) != 0 );

			FKeyEvent event( FInput::Get().GetKeyFromCode( key ), modState, (EInputAction) action, false, scancode, key );
			self->OnInputEvent.Invoke( event );
		});

		glfwSetMouseButtonCallback( m_pWindow, []( GLFWwindow* window, int button, int action, int mods ) {
			CWindowsWindow* self = (CWindowsWindow*) glfwGetWindowUserPointer( window );
			FModifierKeysState modState( ( mods & GLFW_MOD_SHIFT ) != 0, ( mods & GLFW_MOD_SHIFT ) != 0,
										 ( mods & GLFW_MOD_CONTROL ) != 0, ( mods & GLFW_MOD_CONTROL ) != 0,
										 ( mods & GLFW_MOD_ALT ) != 0, ( mods & GLFW_MOD_ALT ) != 0,
										 ( mods & GLFW_MOD_CAPS_LOCK ) != 0 );

			FKeyEvent event( FInput::Get().GetKeyFromCode( button ), modState, (EInputAction)action, false, 0, button );
			self->OnInputEvent.Invoke( event );
		});

		glfwSetCursorPosCallback( m_pWindow, [](GLFWwindow* pWindow, double xPos, double yPos) {
			CWindowsWindow* self = (CWindowsWindow*) glfwGetWindowUserPointer( pWindow );
			CH_CORE_ASSERT( self, "Native window was nullptr, which should never happen here." );

			FCursorEvent event( EKeys::Mouse2D, xPos, yPos );
			self->OnInputEvent.Invoke( event );
		} );

		glfwSetWindowMaximizeCallback( m_pWindow, []( GLFWwindow* window, int maximized ) {
			CWindowsWindow* self = (CWindowsWindow*) glfwGetWindowUserPointer( window );
			self->OnWindowEvent.Invoke( FWindowMaximizeEvent( !maximized ) );
		} );

		glfwSetWindowSizeCallback( m_pWindow, []( GLFWwindow* pWindow, int width, int height ) {
			CH_CORE_LOG( "Window size event: w{0}, h{1}", width, height );

			glClearColor( 0.2f, 0.25f, 0.3f, 1.0f );
			glClear( GL_COLOR_BUFFER_BIT );
			glfwSwapBuffers( pWindow );
		} );

		if ( !( gladLoadGLLoader( (GLADloadproc)( glfwGetProcAddress ) ) ) )
		{
			CH_CORE_ERROR( "Failed to initialize OpenGL context" );
			exit( 1 );
		}


	}

	void CWindowsWindow::Shutdown()
	{
		// destroy window
		// decrement window counter
		// terminate glfw if counter zero
		glfwDestroyWindow( m_pWindow );
		glfwTerminate();
	}

	void CWindowsWindow::Update()
	{
		glfwPollEvents();

		glClearColor( 0.2f, 0.25f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		glfwSwapBuffers( m_pWindow );
	}

	unsigned int CWindowsWindow::GetWidth()
	{
		return m_windowDefinition.Width;
	}

	unsigned int CWindowsWindow::GetHeight()
	{
		return m_windowDefinition.Height;
	}

}