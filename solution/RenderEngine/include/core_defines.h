#pragma once

#ifdef __ANDROID__
	#define SRE_API
#elif SRE_DLL_EXPORT
	#define SRE_API __declspec(dllexport)
#else
	#define SRE_API __declspec(dllimport)
#endif

#define UNSTABLE_EDITOR !defined(RELEASE) && !defined(__ANDROID__)
