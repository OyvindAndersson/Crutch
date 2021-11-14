#pragma once

#include "Core.h"

#ifdef CH_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define CH_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CH##type##ERROR(msg, __VA_ARGS__); CH_DEBUGBREAK(); } }
#define CH_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CH_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define CH_INTERNAL_ASSERT_NO_MSG(type, check) CH_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CH_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define CH_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define CH_INTERNAL_ASSERT_GET_MACRO(...) CH_EXPAND_MACRO( CH_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CH_INTERNAL_ASSERT_WITH_MSG, CH_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define CH_ASSERT(...) CH_EXPAND_MACRO( CH_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define CH_CORE_ASSERT(...) CH_EXPAND_MACRO( CH_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define CH_ASSERT(...)
#define CH_CORE_ASSERT(...)
#endif