#pragma once
#include <map>

namespace Crutch
{

	//--------------------------------------------------
	// 
	//--------------------------------------------------
	struct FModifierKeysState
	{
		FModifierKeysState()
			: m_bIsLeftShiftDown(false)
			, m_bIsRightShiftDown(false)
			, m_bIsLeftCtrlDown(false)
			, m_bIsRightCtrlDown(false)
			, m_bIsLeftAltDown(false)
			, m_bIsRightAltDown(false)
			, m_bAreCapsLocked(false)
		{}

		FModifierKeysState( bool leftShiftDown, bool rightShiftDown, bool leftCtrlDown, bool rightCtrlDown, bool leftAltDown, bool rightAltDown, bool capsLocked )
			: m_bIsLeftShiftDown( leftShiftDown )
			, m_bIsRightShiftDown( rightShiftDown )
			, m_bIsLeftCtrlDown( leftCtrlDown )
			, m_bIsRightCtrlDown( rightCtrlDown )
			, m_bIsLeftAltDown( leftAltDown )
			, m_bIsRightAltDown( rightAltDown )
			, m_bAreCapsLocked( capsLocked )
		{}


		bool IsShiftDown() const { return m_bIsLeftShiftDown || m_bIsRightShiftDown; }
		bool IsCtrlDown() const { return m_bIsLeftCtrlDown || m_bIsRightCtrlDown; }
		bool IsAltDown() const { return m_bIsLeftAltDown || m_bIsRightAltDown; }
		bool AreCapsLocked() const { return m_bAreCapsLocked; }

	private:
		uint16_t m_bIsLeftShiftDown : 1;
		uint16_t m_bIsRightShiftDown : 1;
		
		uint16_t m_bIsLeftCtrlDown : 1;
		uint16_t m_bIsRightCtrlDown : 1;

		uint16_t m_bIsLeftAltDown : 1;
		uint16_t m_bIsRightAltDown : 1;

		uint16_t m_bAreCapsLocked : 1;
	};

	//--------------------------------------------------
	// 
	//--------------------------------------------------
	struct FKey
	{
		enum EKeyFlags
		{
			GamepadKey  = 1 << 0,		// Any gamepad button
			MouseButton = 1 << 1,		// Mouse buttons
			Touch		= 1 << 2,		// Touch interfaces
			ModifierKey = 1 << 3,		// Modifier keys, Alt, Shift, etc.
			Axis1D		= 1 << 4,		// Single axis input (Left stick X, Left stick Y)
			Axis2D		= 1 << 5,		// Two axes input (Left Stick, Right Stick)
			Axis3D		= 1 << 6,		// I.e: Controller tilt sensor

			NoFlags		= 0,
		};

		FKey() {}
		//FKey( const FKey& other ) { /*CH_CORE_LOG( "FKey copy" );*/ }
		FKey( const std::string& name,uint32_t keyFlags = 0 );

		bool IsModifierKey() const { return m_bIsModifierKey != 0; }
		bool IsMouseButton() const { return m_bIsMouseButton != 0; }
		bool IsAxis1D() const { return m_axisType == EInputAxisType::Axis1D; }
		bool IsAxis2D() const { return m_axisType == EInputAxisType::Axis2D; }
		bool IsAxis3D() const { return m_axisType == EInputAxisType::Axis3D; }

		const std::string& GetName() const { return m_name; }

		friend bool operator== ( const FKey& lhs, const FKey& rhs ) { return lhs.m_name == rhs.m_name; }
		friend bool operator!= ( const FKey& lhs, const FKey& rhs ) { return lhs.m_name != rhs.m_name; }

	private:
		friend struct EKeys;
		enum class EInputAxisType : uint8_t
		{
			None,
			Button,
			Axis1D,
			Axis2D,
			Axis3D,
		};

	private:
		std::string m_name;

		uint8_t m_bIsModifierKey : 1;
		uint8_t m_bIsGamepadKey : 1;
		uint8_t m_bIsTouch : 1;
		uint8_t m_bIsMouseButton : 1;
		EInputAxisType m_axisType;
	};

	//--------------------------------------------------
	// Basically an extended enum type to hold some
	// additional data for each key
	//--------------------------------------------------
	struct EKeys
	{
		static const FKey AnyKey;		// GLFW_KEY_UNKNOWN -1
		static const FKey Space;		// GLFW_KEY_SPACE 32

		static const FKey MouseX;
		static const FKey MouseY;
		static const FKey Mouse2D;
		static const FKey MouseScrollUp;
		static const FKey MouseScrollDown;
		static const FKey MouseScrollAxis;

		static const FKey LeftMouseButton;
		static const FKey RightMouseButton;
		static const FKey MiddleMouseButton;
		static const FKey ThumbMouseButton;
		static const FKey ThumbMouseButton2;

		static const FKey Zero;
		static const FKey One;
		static const FKey Two;
		static const FKey Three;
		static const FKey Four;
		static const FKey Five;
		static const FKey Six;
		static const FKey Seven;
		static const FKey Eight;
		static const FKey Nine;

		static const FKey A;
		static const FKey B;
		static const FKey C;
		static const FKey D;
		static const FKey E;
		static const FKey F;
		static const FKey G;
		static const FKey H;
		static const FKey I;
		static const FKey J;
		static const FKey K;
		static const FKey L;
		static const FKey M;
		static const FKey N;
		static const FKey O;
		static const FKey P;
		static const FKey Q;
		static const FKey R;
		static const FKey S;
		static const FKey T;
		static const FKey U;
		static const FKey V;
		static const FKey W;
		static const FKey X;
		static const FKey Y;
		static const FKey Z;

		FKey GetKeyFromCode( uint32_t keyCode );
	};

	//--------------------------------------------------
	// 
	//--------------------------------------------------
	struct FInput
	{
		static FInput& Get() { return *s_Instance; }

		void InitializeMappings();

		FKey GetKeyFromCode( int keyCode ) const;
		int32_t GetCodeFromKey( const FKey& key );

		bool IsKeyPressed( const FKey& key );
		float GetAxisValue( const FKey& key );
		// glm::vec2 Get2DAxisValue( const FKey& key );
		// glm::vec3 Get3DAxisValue( const FKey& key );

	private:
		FInput()
		{
			InitializeMappings();
		}

	private:
		static TSharedPtr<FInput> s_Instance;
		std::map<int32_t, FKey> m_keyMapping;
		
	};
}