#pragma once

#ifdef GK_PLATFORM_WINDOWS
	#ifdef GK_BUILD_DLL
		#define GONK_API __declspec(dllexport)
	#else
		#define GONK_API __declspec(dllimport)
	#endif
#else
	#error Gonk only supports Windows!
#endif