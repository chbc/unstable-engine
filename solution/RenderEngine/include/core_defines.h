#pragma once

#if defined(_WIN32)
    #ifdef SRE_DLL_EXPORT
        #define SRE_API __declspec(dllexport)
    #else
        #define SRE_API __declspec(dllimport)
    #endif
#else
    #define SRE_API
#endif

#define UNSTABLE_EDITOR !defined(RELEASE) && !defined(__ANDROID__)
