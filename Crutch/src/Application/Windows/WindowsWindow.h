#pragma once

#include "../Generic/Window.h"

namespace Crutch
{

	class CWindowsWindow : public IWindowInterface
	{
	public:
		CWindowsWindow( const FWindowProperties& properties );
		virtual ~CWindowsWindow();


	private:
		void Init( const FWindowProperties& properties );
		void Shutdown();
		
		void Update() override;


	public:
		unsigned int GetWidth() override;
		unsigned int GetHeight() override;


	private:
		struct FWindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
		};

		FWindowData m_wndData;
		GLFWwindow* m_pWindow;
	};

}