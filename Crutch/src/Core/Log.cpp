#include "chpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Crutch 
{

	// Definitions
	TSharedPtr<spdlog::logger> CLog::m_CoreLogger;
	TSharedPtr<spdlog::logger> CLog::m_ClientLogger;

	void CLog::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back( MakeShared<spdlog::sinks::stdout_color_sink_mt>() );
		logSinks.emplace_back( MakeShared<spdlog::sinks::basic_file_sink_mt>( "crutch.log", true ) );

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");
		
		m_CoreLogger = MakeShared<spdlog::logger>( "CRUTCH", begin( logSinks ), end( logSinks ) );
		m_ClientLogger = MakeShared<spdlog::logger>( "APP", begin( logSinks ), end( logSinks ) );

		spdlog::register_logger( m_CoreLogger );
		spdlog::register_logger( m_ClientLogger );

		m_CoreLogger->set_level( spdlog::level::trace );
		m_ClientLogger->set_level( spdlog::level::trace );

		m_CoreLogger->flush_on( spdlog::level::trace );
		m_ClientLogger->flush_on( spdlog::level::trace );
	}
}