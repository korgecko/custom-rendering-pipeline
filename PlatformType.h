#pragma once
#include <cstdint>

//~ Windows.h
#define _TCHAR_DEFINED  // TCHAR 재정의 에러 때문
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#undef max
#undef min

#ifndef FORCEINLINE
    // inline을 강제하는 매크로
    #define FORCEINLINE __forceinline

    // inline을 하지않는 매크로
    #define FORCENOINLINE __declspec(noinline)
#endif

#ifdef _DEBUG
    #define FORCEINLINE_DEBUGGABLE inline
#else
    #define FORCEINLINE_DEBUGGABLE FORCEINLINE
#endif

