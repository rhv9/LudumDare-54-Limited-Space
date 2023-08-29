#pragma once

#ifdef GK_PLATFORM_WINDOWS
#ifdef GK_DYANMIC_LINK
	#ifdef GK_BUILD_DLL
		#define GONK_API __declspec(dllexport)
	#else
		#define GONK_API __declspec(dllimport)
	#endif
#else
#define GONK_API
#endif
#else
	#error Gonk only supports Windows!
#endif

#ifdef GK_DEBUG
	#define GK_ENABLE_ASSERTS
#endif

#ifdef GK_ENABLE_ASSERTS
	#define GK_ASSERT(x,...) { if (!(x)) { GK_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();} } 
	#define GK_CORE_ASSERT(x,...) { if (!(x)) { GK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} } 
#else
	#define GK_ASSERT(x, ...) 
	#define GK_CORE_ASSERT(x, ...)
#endif
#define BIT(x) (1 << x)