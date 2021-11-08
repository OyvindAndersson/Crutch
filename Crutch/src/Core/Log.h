#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>

namespace Crutch {

	class CHAPI Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	};

}

// For logging inside core
#define CH_CORE_LOG(...)	::Crutch::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CH_CORE_INFO(...)	::Crutch::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CH_CORE_WARN(...)	::Crutch::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CH_CORE_ERROR(...)	::Crutch::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CH_CORE_CRIT(...)	::Crutch::Log::GetCoreLogger()->critical(__VA_ARGS__)

// For logging by client
#define CH_LOG(...)		::Crutch::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CH_INFO(...)	::Crutch::Log::GetClientLogger()->info(__VA_ARGS__)
#define CH_WARN(...)	::Crutch::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CH_ERROR(...)	::Crutch::Log::GetClientLogger()->error(__VA_ARGS__)
#define CH_CRIT(...)	::Crutch::Log::GetClientLogger()->critical(__VA_ARGS__)