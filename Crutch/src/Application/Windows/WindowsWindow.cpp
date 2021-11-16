#include "chpch.h"
#include "WindowsWindow.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Crutch
{

	CWindowsWindow::CWindowsWindow( const FWindowProperties& properties )
	{
		Init( properties );
	}
	CWindowsWindow::~CWindowsWindow()
	{
		Shutdown();
	}

	void CWindowsWindow::Init( const FWindowProperties& properties )
	{
		m_wndData.Title = properties.Title;
		m_wndData.Width = properties.Width;
		m_wndData.Height = properties.Height;
		m_wndData.VSync = true;

		glfwInit();

#ifdef CH_DEBUG
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		//glfwWindowHint( GLFW_RESIZABLE, GL_TRUE );
#endif

		m_pWindow = glfwCreateWindow( 
			m_wndData.Width, 
			m_wndData.Height, 
			m_wndData.Title.c_str(), 
			nullptr, nullptr );

		if ( !m_pWindow )
		{
			CH_CORE_ERROR( "Failed to create GLFW window!" );
			glfwTerminate();
			exit( 1 );
		}

		glfwMakeContextCurrent( m_pWindow );

		// Bind events
		glfwSetKeyCallback( m_pWindow, []( GLFWwindow* window, int key, int scancode, int action, int mode ) {
			CH_CORE_LOG( "KEY  code: {0:d}, scancode: {1:d}, action: {2:d}, mode: {3:d}  ", key, scancode, action, mode );

			if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
				glfwSetWindowShouldClose( window, GL_TRUE );
			} );


		if ( !( gladLoadGLLoader( (GLADloadproc)( glfwGetProcAddress ) ) ) )
		{
			CH_CORE_ERROR( "Failed to initialize OpenGL context" );
			exit( 1 );
		}

		glViewport( 0, 0, m_wndData.Width, m_wndData.Height );
		
		// 1. Check if window count is zero, then init Glfw
		// 2. If debug enabled, set glfwWindowHints
		// 3. create window and increment window counter
		// 4. set context, and init
		// 5. glfwSetWindowUserPointer window - data
		// 6. Set vsync true
		// 7. Set glfw callbacks -- size, close, key, mouse, char, scroll, cursor
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
		while ( !glfwWindowShouldClose( m_pWindow ) )
		{
			glfwPollEvents();

			glClearColor( 0.2f, 0.25f, 0.3f, 1.0f );
			glClear( GL_COLOR_BUFFER_BIT );

			glfwSwapBuffers( m_pWindow );
		}
	}

	unsigned int CWindowsWindow::GetWidth()
	{
		return m_wndData.Width;
	}

	unsigned int CWindowsWindow::GetHeight()
	{
		return m_wndData.Height;
	}

}