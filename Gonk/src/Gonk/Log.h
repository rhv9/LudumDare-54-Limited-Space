#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Gonk {

	class GONK_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

// Core log macros
#define GK_CORE_TRACE(...)       ::Gonk::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GK_CORE_INFO(...)        ::Gonk::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GK_CORE_WARN(...)        ::Gonk::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GK_CORE_ERROR(...)       ::Gonk::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GK_CORE_CRITICAL(...)    ::Gonk::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define GK_TRACE(...)            ::Gonk::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GK_INFO(...)             ::Gonk::Log::GetClientLogger()->info(__VA_ARGS__)
#define GK_WARN(...)             ::Gonk::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GK_ERROR(...)            ::Gonk::Log::GetClientLogger()->error(__VA_ARGS__)
#define GK_CRITICAL(...)         ::Gonk::Log::GetClientLogger()->critical(__VA_ARGS__)

