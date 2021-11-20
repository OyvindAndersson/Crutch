#pragma once

#include <memory>

namespace Crutch
{

	/* 
		Unique pointer - wrap std::version for now 
	*/
	template<typename Type>
	using TUniquePtr = std::unique_ptr<Type>;

	template <typename Type, typename... Args>
	constexpr TUniquePtr<Type> MakeUnique( Args&& ... args )
	{
		return std::make_unique<Type>( std::forward<Args>( args )... );
	}

	/* 
		Shared pointer - wrap std:: version for now 
	*/
	template<typename Type>
	using TSharedPtr = std::shared_ptr<Type>;

	template <typename Type, typename... Args>
	constexpr TSharedPtr<Type> MakeShared( Args&& ... args )
	{
		return std::make_shared<Type>( std::forward<Args>( args )... );
	}

	/*
		Weak pointer - wrap std:: version for now
	*/
	template<typename Type>
	using TWeakPtr = std::weak_ptr<Type>;


}