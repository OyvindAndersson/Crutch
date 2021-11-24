#include "chpch.h"
#include "Application/Generic/Application.h"
#include "Input.h"

#include "GLFW/glfw3.h"

namespace Crutch
{
	TSharedPtr<CInput> CInput::m_instance = MakeShared<CInput>( CInput() );

	bool CInput::IsKeyPressed( const EKeyCode& key )
	{
		auto pWindow = static_cast<GLFWwindow*>( CApplication::Get().GetWindow().GetNativeWindow() );
		EInputAction state = static_cast<EInputAction> ( glfwGetKey( pWindow, static_cast<int>( key ) ) );
		return state == EInputAction::Pressed || state == EInputAction::Repeat;
	}

// 	const Crutch::FVector2D& CInput::GetMousePos()
// 	{
// 		auto pWindow = static_cast<GLFWwindow*>( CApplication::Get().GetWindow().GetNativeWindow() );
// 
// 		double xpos, ypos;
// 		glfwGetCursorPos( pWindow, &xpos, &ypos );
// 
// 		return FVector2D( static_cast<float>(xpos), static_cast<float>(ypos) );
// 	}

	

}