#include "chpch.h"
#include "WindowsWindow.h"

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