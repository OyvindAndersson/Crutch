#pragma once

#include "chpch.h"

namespace Crutch {

#define DECLARE_DELEGATE(delegateName)												typedef TDelegate<void()> delegateName
#define DECLARE_DELEGATE_OneParam(delegateName, par0)								typedef TDelegate<void(par0)> delegateName
#define DECLARE_DELEGATE_TwoParam(delegateName, par0, par1)							typedef TDelegate<void(par0, par1)> delegateName
																							
#define DECLARE_DELEGATE_RetVal(delegateName, ret)									typedef TDelegate<ret()> delegateName
#define DECLARE_DELEGATE_RetVal_OneParam(delegateName, ret, par0)					typedef TDelegate<ret(par0)> delegateName
#define DECLARE_DELEGATE_RetVal_TwoParam(delegateName, ret, par0, par1)				typedef TDelegate<ret(par0, par1)> delegateName

#define DECLARE_MULTICAST_DELEGATE(delegateName)									typedef TMulticastDelegate<void()> delegateName
#define DECLARE_MULTICAST_DELEGATE_OneParam(delegateName, par0)						typedef TMulticastDelegate<void(par0)> delegateName
#define DECLARE_MULTICAST_DELEGATE_TwoParam(delegateName, par0, par1)				typedef TMulticastDelegate<void(par0, par1)> delegateName

#define DECLARE_MULTICAST_DELEGATE_RetVal(delegateName, ret)						typedef TMulticastDelegate<ret()> delegateName
#define DECLARE_MULTICAST_DELEGATE_RetVal_OneParam(delegateName, ret, par0)			typedef TMulticastDelegate<ret(par0)> delegateName
#define DECLARE_MULTICAST_DELEGATE_RetVal_TwoParam(delegateName, ret, par0, par1)	typedef TMulticastDelegate<ret(par0, par1)> delegateName

	template <typename Signature>
	class TDelegate;

	/**** namespace scope swap function ****/
	template <typename Signature>
	void swap( TDelegate<Signature>& d1, TDelegate<Signature>& d2)
	{
		d1.Swap(d2);
	}

	/**** delegate partial class template for function types ****/
	template <typename Ret, typename... Args>
	class TDelegate<Ret(Args...)>
	{
	public:
		TDelegate();
		TDelegate( TDelegate const& other);	// copy
		TDelegate( TDelegate&& other);			// move

		~TDelegate();

		TDelegate& operator=( TDelegate const& other);	// assign existing
		TDelegate& operator=( TDelegate&& other);		// move existing

		template <auto FreeFunction>
		void Bind();						// .Bind<MyFreeFunction>();

		template <auto Callable, typename Type>
		void Bind(Type& instance);			// .Bind<&MyClass::MemberFunction>( instance );

		template <typename Type>
		void Bind(Type&& funObj);			// .Bind( lambda )

		void Swap( TDelegate& other);

		explicit operator bool() const { return m_Function; }

		Ret operator()(Args... args);
		Ret Invoke(Args... args);

	private:
		using Storage = std::aligned_storage_t<sizeof(void*), alignof(void*)>;
		using Function = Ret(*)(void*, Args...);

		Storage m_data;
		Function m_Function;

		bool m_isStored = false;

		using DestroyStorageFunction = void(*)( TDelegate*);
		using CopyStorageFunction	 = void(*)(const TDelegate*, TDelegate*);
		using MoveStorageFunction	 = void(*)( TDelegate*, TDelegate*);

		DestroyStorageFunction  m_DestroyStorage = nullptr;
		CopyStorageFunction		m_CopyStorage = nullptr;
		MoveStorageFunction		m_MoveStorage = nullptr;

		/**** helper function templates for special member functions ****/
		template <typename Type>
		static void DestroyStorage( TDelegate* delegate)
		{
			reinterpret_cast<Type*>(&delegate->m_data)->~Type();
		}

		template <typename Type>
		static void CopyStorage(const TDelegate* src, TDelegate* dst)
		{
			new(&dst->m_data) Type(*reinterpret_cast<const Type*>(&src->m_data));
		}

		template <typename Type>
		static void MoveStorage( TDelegate* src, TDelegate* dst)
		{
			new(&dst->m_data) Type(std::move(*reinterpret_cast<Type*>(&src->m_data)));
		}
	};

	template <typename Ret, typename... Args>
	TDelegate<Ret(Args...)>::TDelegate()
	{
		new(&m_data) std::nullptr_t(nullptr);

		m_Function = nullptr;
	}

	template <typename Ret, typename... Args>
	TDelegate<Ret(Args...)>::TDelegate( TDelegate const& other)
	{
		if (other.m_isStored)
		{
			other.m_CopyStorage(&other, this);

			m_DestroyStorage = other.m_DestroyStorage;
			m_CopyStorage = other.m_CopyStorage;
			m_MoveStorage = other.m_MoveStorage;

			m_isStored = true;
		}
		else
			m_data = other.m_data;

		m_Function = other.m_Function;
	}

	template <typename Ret, typename... Args>
	TDelegate<Ret(Args...)>::TDelegate( TDelegate&& other)
	{
		if (other.m_isStored)
		{
			other.m_MoveStorage(&other, this);

			m_DestroyStorage =	other.m_DestroyStorage;
			m_CopyStorage =		other.m_CopyStorage;
			m_MoveStorage =		other.m_MoveStorage;

			m_isStored = true;
		}
		else
			m_data = other.m_data;

		m_Function = other.m_Function;
	}

	template <typename Ret, typename... Args>
	TDelegate<Ret(Args...)>::~TDelegate()
	{
		if (m_isStored)
			m_DestroyStorage(this);
	}

	template <typename Ret, typename... Args>
	TDelegate<Ret(Args...)>& TDelegate<Ret(Args...)>::operator=( TDelegate const& other)
	{
		TDelegate temp(other);
		Swap(temp);

		return *this;
	}

	template <typename Ret, typename... Args>
	TDelegate<Ret(Args...)>& TDelegate<Ret(Args...)>::operator=( TDelegate&& other)
	{
		TDelegate temp(std::move(other));
		Swap(temp);

		return *this;
	}

	template <typename Ret, typename... Args>
	template <auto FreeFunction>
	void TDelegate<Ret(Args...)>::Bind()
	{
		new(&m_data) std::nullptr_t(nullptr);

		m_Function = +[](void*, Args... args) -> Ret
		{
			return FreeFunction(std::forward<Args>(args)...);
		};
	}

	template <typename Ret, typename... Args>
	template <auto Callable, typename Type>
	void TDelegate<Ret(Args...)>::Bind(Type& instance)
	{
		new(&m_data) Type* (&instance);

		m_Function = +[](void* data, Args... args) -> Ret
		{
			Storage* storage = static_cast<Storage*>(data);
			Type* instance = *reinterpret_cast<Type**>(storage);
			return std::invoke(Callable, instance, std::forward<Args>(args)...);
		};
	}

	template <typename Ret, typename... Args>
	template <typename Type>
	void TDelegate<Ret(Args...)>::Bind(Type&& funObj)
	{
		static_assert(sizeof(Type) <= sizeof(void*));

		if constexpr (std::is_lvalue_reference<Type>::value)
		{
			new(&m_data) std::remove_reference_t<Type>* (&funObj);

			m_Function = +[](void* data, Args... args) -> Ret
			{
				Storage* storage = static_cast<Storage*>(data);
				std::remove_reference_t<Type>* instance = *reinterpret_cast<std::remove_reference_t<Type>**>(storage);
				return std::invoke(*instance, std::forward<Args>(args)...);
			};
		}
		else
		{
			new(&m_data) Type(std::move(funObj));
			m_DestroyStorage = &DestroyStorage<Type>;
			m_isStored = true;

			m_Function = +[](void* data, Args... args) -> Ret
			{
				Storage* storage = static_cast<Storage*>(data);
				std::remove_reference_t<Type>* instance = reinterpret_cast<std::remove_reference_t<Type>*>(storage);
				return std::invoke(*instance, std::forward<Args>(args)...);
			};
		}
	}

	template <typename Ret, typename... Args>
	Ret TDelegate<Ret(Args...)>::operator()(Args... args)
	{
		return m_Function(&m_data, std::forward<Args>(args)...);
	}

	template <typename Ret, typename... Args>
	Ret TDelegate<Ret(Args...)>::Invoke(Args... args)
	{
		return m_Function(&m_data, std::forward<Args>(args)...);
	}

	template <typename Ret, typename... Args>
	void TDelegate<Ret(Args...)>::Swap( TDelegate& other)
	{
		if (other.m_isStored)
			other.m_CopyStorage(&other, this);
		else
			m_data = other.m_data;

		Function tempFunction = m_Function;
		m_Function = other.m_Function;
		other.m_Function = tempFunction;

		bool tempStored = m_isStored;
		m_isStored = other.m_isStored;
		other.m_isStored = tempStored;

		DestroyStorageFunction tempDestroyFun = m_DestroyStorage;
		m_DestroyStorage = other.m_DestroyStorage;
		other.m_DestroyStorage = tempDestroyFun;

		CopyStorageFunction tempCopyFun = m_CopyStorage;
		m_CopyStorage = other.m_CopyStorage;
		other.m_CopyStorage = tempCopyFun;

		MoveStorageFunction tempMoveFun = m_MoveStorage;
		m_MoveStorage = other.m_MoveStorage;
		other.m_MoveStorage = tempMoveFun;
	}

	//-------------------------------------------------------------------------------------

	template <typename Signature>
	class TMulticastDelegate;

	template <typename Ret, typename... Args>
	class TMulticastDelegate<Ret(Args...)>
	{
	public:
		TMulticastDelegate(std::size_t size = 10U) { m_delegates.reserve(size); }

		template <auto Callable>
		void Bind();

		template <auto Callable, typename Type>
		void Bind(Type& instance);

		template <typename Type>
		void Bind(Type&& funObj);

		explicit operator bool() const { return !m_delegates.empty(); }

		void operator()(Args... args) { for (auto& delegate : m_delegates) delegate(std::forward<Args>(args)...); }
		void Invoke(Args... args) { for (auto& delegate : m_delegates) delegate.Invoke(std::forward<Args>(args)...); }
	private:
		std::vector<TDelegate<Ret(Args...)>> m_delegates;
	};

	template <typename Ret, typename... Args>
	template <auto Callable>
	void TMulticastDelegate<Ret(Args...)>::Bind()
	{
		TDelegate<Ret(Args...)> delegate;
		m_delegates.push_back(delegate);

		m_delegates.back().template Bind<Callable>();
	}

	template <typename Ret, typename... Args>
	template <auto Callable, typename Type>
	void TMulticastDelegate<Ret(Args...)>::Bind(Type& instance)
	{
		TDelegate<Ret(Args...)> delegate;
		m_delegates.push_back(delegate);

		m_delegates.back().template Bind<Callable>(instance);
	}

	template <typename Ret, typename... Args>
	template <typename Type>
	void TMulticastDelegate<Ret(Args...)>::Bind(Type&& funObj)
	{
		TDelegate<Ret(Args...)> delegate;
		m_delegates.push_back(delegate);

		m_delegates.back().Bind(std::forward<Type>(funObj));
	}

}