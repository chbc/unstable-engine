#pragma once

#ifdef SRE_DLL_EXPORT
#define SRE_API __declspec( dllexport )
#else
#define SRE_API __declspec(dllimport)
#endif
