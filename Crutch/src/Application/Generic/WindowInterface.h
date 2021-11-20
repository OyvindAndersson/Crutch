#pragma once

#include "Core/Core.h"
#include "Core/Pointers.h"
#include "Events/Events.h"

namespace Crutch
{
	DECLARE_DELEGATE_OneParam( FInputEventDelegate, FInputEvent& );
	DECLARE_DELEGATE_OneParam( FWindowEventDelegate, FWindowEvent& );

	//--------------------------------------------------
	// Defines typical properties of a window (size and settings)
	//--------------------------------------------------
	struct FWindowDefinition
	{
		uint32_t Width;
		uint32_t Height;
		std::string Title;

		FWindowDefinition( const std::string& title = "Crutch Engine", uint32_t width = 1280, uint32_t height = 720 ) :
			Width( width ), Height( height ), Title( title ) { }
	};

	//--------------------------------------------------
	// Base interface for all window types
	//--------------------------------------------------
	class IWindowInterface
	{
	public:
		virtual ~IWindowInterface() = default;

		virtual void Initialize( class CApplication* const application, const FWindowDefinition& definition ) = 0;
		virtual void Update() = 0;

	public:
		FInputEventDelegate OnInputEvent;
		FWindowEventDelegate OnWindowEvent;

	public:
		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;
		virtual void* GetNativeWindow() const = 0;

		// Factory func that creates the platform specific window type
		static TUniquePtr<IWindowInterface> Create();
	};

}