#include "chpch.h"
#include "Application.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Crutch {

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

		CH_CORE_INFO( "Starting GLFW context, OpenGl 4.6" );

		glfwInit();

		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		glfwWindowHint( GLFW_RESIZABLE, GL_TRUE );

		GLFWwindow* window = glfwCreateWindow( 1280, 720, "Crutch Engine", nullptr, nullptr );
		
		glfwMakeContextCurrent( window );

		if ( !window )
		{
			CH_CORE_ERROR( "Failed to create GLFW window!" );
			glfwTerminate();
			exit( 1 );
		}

		glfwSetKeyCallback( window, []( GLFWwindow* window, int key, int scancode, int action, int mode ) {
			CH_CORE_LOG( "KEY  code: {0:d}, scancode: {1:d}, action: {2:d}, mode: {3:d}  ", key, scancode, action, mode );

			if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
				glfwSetWindowShouldClose( window, GL_TRUE );
		} );

		if ( ! (gladLoadGLLoader( (GLADloadproc)( glfwGetProcAddress) )) )
		{
			CH_CORE_ERROR( "Failed to initialize OpenGL context" );
			exit( 1 );
		}

		glViewport( 0, 0, 1280, 720 );

		while ( !glfwWindowShouldClose( window ) )
		{
			glfwPollEvents();

			glClearColor( 0.2f, 0.25f, 0.3f, 1.0f );
			glClear( GL_COLOR_BUFFER_BIT );

			glfwSwapBuffers( window );
		}

		glfwTerminate();

		// Keep console open after termination
		while ( true );
	}

}