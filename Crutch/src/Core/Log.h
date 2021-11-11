#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>

namespace Crutch {

	class CLog
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
#define CH_CORE_LOG(...)	::Crutch::CLog::GetCoreLogger()->trace(__VA_ARGS__)
#define CH_CORE_INFO(...)	::Crutch::CLog::GetCoreLogger()->info(__VA_ARGS__)
#define CH_CORE_WARN(...)	::Crutch::CLog::GetCoreLogger()->warn(__VA_ARGS__)
#define CH_CORE_ERROR(...)	::Crutch::CLog::GetCoreLogger()->error(__VA_ARGS__)
#define CH_CORE_CRIT(...)	::Crutch::CLog::GetCoreLogger()->critical(__VA_ARGS__)

// For logging by client
#define CH_LOG(...)			::Crutch::CLog::GetClientLogger()->trace(__VA_ARGS__)
#define CH_INFO(...)		::Crutch::CLog::GetClientLogger()->info(__VA_ARGS__)
#define CH_WARN(...)		::Crutch::CLog::GetClientLogger()->warn(__VA_ARGS__)
#define CH_ERROR(...)		::Crutch::CLog::GetClientLogger()->error(__VA_ARGS__)
#define CH_CRIT(...)		::Crutch::CLog::GetClientLogger()->critical(__VA_ARGS__)