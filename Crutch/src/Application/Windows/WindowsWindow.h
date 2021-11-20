#pragma once

#include "../Generic/WindowInterface.h"
#include "Events/Events.h"

struct GLFWwindow;

namespace Crutch
{
	

	//--------------------------------------------------
	// Window class for Windows OS
	//--------------------------------------------------
	class CWindowsWindow : public IWindowInterface
	{
	public:
		CWindowsWindow();
		virtual ~CWindowsWindow();

	private:
		void Initialize( class CApplication* const application, const FWindowDefinition& definition ) override;
		void Shutdown();
		void Update() override;

	public:
		unsigned int GetWidth() override;
		unsigned int GetHeight() override;

		virtual void* GetNativeWindow() const override { return m_pWindow; }

	private:
		FWindowDefinition	m_windowDefinition;
		GLFWwindow*			m_pWindow;

	};

}