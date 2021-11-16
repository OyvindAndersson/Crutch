#pragma once

#include "Core/Core.h"

namespace Crutch
{
	struct FWindowProperties
	{
		uint32_t Width;
		uint32_t Height;
		std::string Title;

		FWindowProperties( const std::string& title = "Crutch Engine", uint32_t width = 1280, uint32_t height = 720 ) :
			Width( width ), Height( height ), Title( title )
		{
		}

		static FWindowProperties Default;
	};

	static FWindowProperties Default;

	class IWindowInterface
	{
	public:
		virtual ~IWindowInterface() = default;

	public:
		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;

		virtual void Update() = 0;

		static TUniquePtr<IWindowInterface> Create( const FWindowProperties& properties = FWindowProperties() );
	};

}