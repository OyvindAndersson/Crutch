#pragma once

#include "Core/Input.h"

namespace Crutch
{
	//--------------------------------------------------
	// Input type events
	//--------------------------------------------------
	enum class EInputAction
	{
		None = 0,
		Pressed = 1,
		Repeat = 2,
		Released = 3
	};

	struct FInputEvent
	{
		FInputEvent()
			: m_modifierKeys( FModifierKeysState() )
			, m_bIsRepeat( false )
		{}

		FInputEvent( const FModifierKeysState& modifierKeys, const bool isRepeat )
			: m_modifierKeys( modifierKeys )
			, m_bIsRepeat( isRepeat )
		{}

		virtual ~FInputEvent() {}

	public:

		bool IsRepeat() const { return m_bIsRepeat; }
		const FModifierKeysState& GetModifierKeys() const { return m_modifierKeys; }

		virtual bool IsCursorEvent() const { return false; }
		virtual bool IsKeyEvent() const { return false; }

	protected:
		FModifierKeysState m_modifierKeys;
		bool m_bIsRepeat;

	};

	struct FKeyEvent : public FInputEvent
	{
		FKeyEvent()
			: FInputEvent( FModifierKeysState(), false )
			, m_inputAction(EInputAction::None)
			, m_key()
			, m_characterCode( 0 )
			, m_keyCode( 0 )
		{ }

		FKeyEvent( const FKey& key, const FModifierKeysState& modifierKeys, const EInputAction inputAction, const bool bIsRepeat, const unsigned int charCode, const unsigned int keyCode )
			: FInputEvent( modifierKeys, bIsRepeat )
			, m_key( key )
			, m_inputAction( inputAction )
			, m_characterCode( charCode )
			, m_keyCode( keyCode )
		{}

		FKey GetKey() const { return m_key; }
		unsigned int GetCharacter() const { return m_characterCode; }
		unsigned int GetKeyCode() const { return m_keyCode; }

		virtual bool IsCursorEvent() const { return false; }
		virtual bool IsKeyEvent() const { return true; }

	private:
		FKey m_key;
		EInputAction m_inputAction;
		unsigned int m_characterCode;
		unsigned int m_keyCode;
	};

	struct FCursorEvent : public FInputEvent
	{
		FCursorEvent( const FKey& key, float xPos, float yPos )
			: FInputEvent()
			, m_key(key)
			, m_fPosX(xPos)
			, m_fPosY(yPos)
		{}

		FKey GetKey() const { return m_key; }
		float GetPosX() const { return m_fPosX; }
		float GetPosY() const { return m_fPosY; }

		virtual bool IsCursorEvent() const { return true; }
		virtual bool IsKeyEvent() const { return false; }

	private:
		FKey m_key;
		float m_fPosX, m_fPosY;
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
