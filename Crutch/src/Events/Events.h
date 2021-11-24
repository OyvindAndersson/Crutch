#pragma once

#include "Core/Input.h"

namespace Crutch
{
	//--------------------------------------------------
	// Input type events
	//--------------------------------------------------

	enum class EInputDeviceType
	{
		Unknown = 0,
		Keyboard = 1,
		Mouse = 2,
		Gamepad = 3
	};

	//--------------------------------------------------
	// All input type events (keyboard, gamepad, mouse, etc)
	//--------------------------------------------------

	struct FInputEvent
	{
		FInputEvent( EInputAction action, FModifierKeyState modState, EInputDeviceType type )
			: Action( action )
			, ModifierState( modState )
			, InputType( type )
		{}

		EInputAction Action;
		FModifierKeyState ModifierState;
		EInputDeviceType InputType;
	};

	struct FKeyEvent : public FInputEvent
	{
		FKeyEvent( EKeyCode key, EInputAction action, FModifierKeyState modsState, int scancode )
			: FInputEvent( action, modsState, EInputDeviceType::Keyboard )
			, Key( key )
			, ScanCode( scancode )
		{}

		EKeyCode Key;
		int ScanCode;
	};

	struct FMouseEvent : public FInputEvent
	{
		FMouseEvent( EMouseCode button, EInputAction action, FModifierKeyState modsState )
			: FInputEvent( action, modsState, EInputDeviceType::Mouse )
			, Button( button )
		{}

		EMouseCode Button;
	};

	//--------------------------------------------------
	// Window type events
	//--------------------------------------------------

	struct FWindowEvent
	{
		FWindowEvent(){}

		virtual bool IsMaximizeEvent() const { return false; }
		virtual bool IsMinimizeEvent() const { return false; }
		virtual bool WasRestored() const { return false; }
	};

	struct FWindowMaximizeEvent : public FWindowEvent
	{
		FWindowMaximizeEvent(bool bWasRestored)
			: FWindowEvent()
			, m_bWasRestored(bWasRestored)
		{}

		virtual bool IsMaximizeEvent() const { return true; }
		virtual bool IsMinimizeEvent() const { return false; }
		virtual bool WasRestored() const { return m_bWasRestored; }

	private:
		bool m_bWasRestored;
	};
}
