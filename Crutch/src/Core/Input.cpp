#include "chpch.h"
#include "Application/Generic/Application.h"
#include "Input.h"

#include "GLFW/glfw3.h"

namespace Crutch
{
	const FKey EKeys::AnyKey( "AnyKey");
	const FKey EKeys::Space( "Space" );

	const FKey EKeys::MouseX( "MouseX", FKey::Axis1D | FKey::MouseButton );
	const FKey EKeys::MouseY( "MouseY", FKey::Axis1D | FKey::MouseButton );
	const FKey EKeys::Mouse2D( "MouseAxis", FKey::Axis2D | FKey::MouseButton );
	const FKey EKeys::MouseScrollUp( "MouseScrollUp", FKey::MouseButton );
	const FKey EKeys::MouseScrollDown( "MouseScrollDown", FKey::MouseButton );
	const FKey EKeys::MouseScrollAxis( "MouseScrollAxis", FKey::Axis2D | FKey::MouseButton );

	const FKey EKeys::LeftMouseButton( "MouseLeftButton", FKey::MouseButton );
	const FKey EKeys::RightMouseButton( "MouseRightButton", FKey::MouseButton );
	const FKey EKeys::MiddleMouseButton( "MouseMiddleButton", FKey::MouseButton );
	const FKey EKeys::ThumbMouseButton( "MouseThumbButton_Back", FKey::MouseButton );
	const FKey EKeys::ThumbMouseButton2( "MouseThumbButton_Fwd", FKey::MouseButton );

	const FKey EKeys::Zero( "Zero" );
	const FKey EKeys::One( "One" );
	const FKey EKeys::Two( "Two" );
	const FKey EKeys::Three( "Three" );
	const FKey EKeys::Four( "Four" );
	const FKey EKeys::Five( "Five" );
	const FKey EKeys::Six( "Six" );
	const FKey EKeys::Seven( "Seven" );
	const FKey EKeys::Eight( "Eight" );
	const FKey EKeys::Nine( "Nine" );

	const FKey EKeys::A( "A" );
	const FKey EKeys::B( "B" );
	const FKey EKeys::C( "C" );
	const FKey EKeys::D( "D" );
	const FKey EKeys::E( "E" );
	const FKey EKeys::F( "F" );
	const FKey EKeys::G( "G" );
	const FKey EKeys::H( "H" );
	const FKey EKeys::I( "I" );
	const FKey EKeys::J( "J" );
	const FKey EKeys::K( "K" );
	const FKey EKeys::L( "L" );
	const FKey EKeys::M( "M" );
	const FKey EKeys::N( "N" );
	const FKey EKeys::O( "O" );
	const FKey EKeys::P( "P" );
	const FKey EKeys::Q( "Q" );
	const FKey EKeys::R( "R" );
	const FKey EKeys::S( "S" );
	const FKey EKeys::T( "T" );
	const FKey EKeys::U( "U" );
	const FKey EKeys::V( "V" );
	const FKey EKeys::W( "W" );
	const FKey EKeys::X( "X" );
	const FKey EKeys::Y( "Y" );
	const FKey EKeys::Z( "Z" );

	FKey::FKey( const std::string& name, uint32_t keyFlags /*= 0 */ )
	{
		m_name = name;

		m_bIsModifierKey = ( ( keyFlags & EKeyFlags::ModifierKey ) != 0 );
		m_bIsMouseButton = ( ( keyFlags & EKeyFlags::MouseButton ) != 0 );
		m_bIsGamepadKey = ( ( keyFlags & EKeyFlags::GamepadKey ) != 0 );

		if ( ( keyFlags & EKeyFlags::Axis1D ) != 0 )
		{
			m_axisType = EInputAxisType::Axis1D;
		}
		else if ( ( keyFlags & EKeyFlags::Axis2D ) != 0 )
		{
			m_axisType = EInputAxisType::Axis2D;
		}
		else if ( ( keyFlags & EKeyFlags::Axis3D ) != 0 )
		{
			m_axisType = EInputAxisType::Axis3D;
		}
		else
		{
			m_axisType = EInputAxisType::None;
		}
	}

	//--------------------------------------------------
	// 
	//--------------------------------------------------
	TSharedPtr<FInput> FInput::s_Instance = MakeShared<FInput>( FInput() );

	void FInput::InitializeMappings()
	{
		m_keyMapping[GLFW_KEY_UNKNOWN] = EKeys::AnyKey;
		m_keyMapping[GLFW_KEY_SPACE] = EKeys::Space;

		m_keyMapping[GLFW_MOUSE_BUTTON_LEFT] = EKeys::LeftMouseButton;
		m_keyMapping[GLFW_MOUSE_BUTTON_RIGHT] = EKeys::RightMouseButton;
		m_keyMapping[GLFW_MOUSE_BUTTON_MIDDLE] = EKeys::MiddleMouseButton;
		m_keyMapping[GLFW_MOUSE_BUTTON_4] = EKeys::ThumbMouseButton;
		m_keyMapping[GLFW_MOUSE_BUTTON_5] = EKeys::ThumbMouseButton2;

		m_keyMapping[GLFW_KEY_0] = EKeys::Zero;
		m_keyMapping[GLFW_KEY_1] = EKeys::One;
		m_keyMapping[GLFW_KEY_2] = EKeys::Two;
		m_keyMapping[GLFW_KEY_3] = EKeys::Three;
		m_keyMapping[GLFW_KEY_4] = EKeys::Four;
		m_keyMapping[GLFW_KEY_5] = EKeys::Five;
		m_keyMapping[GLFW_KEY_6] = EKeys::Six;
		m_keyMapping[GLFW_KEY_7] = EKeys::Seven;
		m_keyMapping[GLFW_KEY_8] = EKeys::Eight;
		m_keyMapping[GLFW_KEY_9] = EKeys::Nine;
		
		m_keyMapping[GLFW_KEY_A] = EKeys::A;
		m_keyMapping[GLFW_KEY_B] = EKeys::B;
		m_keyMapping[GLFW_KEY_C] = EKeys::C;
		m_keyMapping[GLFW_KEY_D] = EKeys::D;
		m_keyMapping[GLFW_KEY_E] = EKeys::E;
		m_keyMapping[GLFW_KEY_F] = EKeys::F;
		m_keyMapping[GLFW_KEY_G] = EKeys::G;
		m_keyMapping[GLFW_KEY_H] = EKeys::H;
		m_keyMapping[GLFW_KEY_I] = EKeys::I;
		m_keyMapping[GLFW_KEY_J] = EKeys::J;
		m_keyMapping[GLFW_KEY_K] = EKeys::K;
		m_keyMapping[GLFW_KEY_L] = EKeys::L;
		m_keyMapping[GLFW_KEY_M] = EKeys::M;
		m_keyMapping[GLFW_KEY_N] = EKeys::N;
		m_keyMapping[GLFW_KEY_O] = EKeys::O;
		m_keyMapping[GLFW_KEY_P] = EKeys::P;
		m_keyMapping[GLFW_KEY_Q] = EKeys::Q;
		m_keyMapping[GLFW_KEY_R] = EKeys::R;
		m_keyMapping[GLFW_KEY_S] = EKeys::S;
		m_keyMapping[GLFW_KEY_T] = EKeys::T;
		m_keyMapping[GLFW_KEY_U] = EKeys::U;
		m_keyMapping[GLFW_KEY_V] = EKeys::V;
		m_keyMapping[GLFW_KEY_W] = EKeys::W;
		m_keyMapping[GLFW_KEY_X] = EKeys::X;
		m_keyMapping[GLFW_KEY_Y] = EKeys::Y;
		m_keyMapping[GLFW_KEY_Z] = EKeys::Z;
	}

	FKey FInput::GetKeyFromCode( int keyCode ) const
	{
		auto it = m_keyMapping.find( keyCode );
		if ( it != m_keyMapping.end() )
		{
			return it->second;
		}
		else
		{
			return EKeys::AnyKey; // Or, add a new key to the mapping list, as it must be a valid code of some kind...?
		}
	}

	int32_t FInput::GetCodeFromKey( const FKey& key )
	{
		for ( auto it = m_keyMapping.begin(); it != m_keyMapping.end(); ++it )
		{
			if ( it->second == key )
				return it->first;
		}

		return -1;
	}

	bool FInput::IsKeyPressed( const FKey& key )
	{
		auto pWindow = static_cast<GLFWwindow*>( CApplication::Get().GetWindow().GetNativeWindow() );
		auto state = glfwGetKey( pWindow, GetCodeFromKey( key ) );
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	float FInput::GetAxisValue( const FKey& key )
	{
		auto pWindow = static_cast<GLFWwindow*>( CApplication::Get().GetWindow().GetNativeWindow() );
		
		CH_CORE_ASSERT( pWindow, "Native window must and should be valid!" );

		if ( key.IsMouseButton() && key.IsAxis1D() )
		{
			double xpos, ypos;
			glfwGetCursorPos( pWindow, &xpos, &ypos );

			if ( key == EKeys::MouseX )
			{
				CH_CORE_INFO( "{0} axis value: {1:f}", key.GetName(), (float) xpos );
				return (float)xpos;
			}
			else
			{
				CH_CORE_INFO( "{0} axis value: {1:f}", key.GetName(), (float) ypos );
				return (float)ypos;
			}
		}
		else
		{
			CH_CORE_INFO( "GetAxisValue from key {0}", key.GetName());
			return 0.0f;
		}
	}

}