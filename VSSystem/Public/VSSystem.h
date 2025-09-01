//
// Created by lix on 2025/8/31.
//
#pragma once
#include "../VSPlatform.h"
#if WINDOWS_PLATFORM
#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <atlsimpstr.h>
#include <intrin.h>
//关闭编译器警告
#endif

#include "../VSSystemExports.h"
namespace VSEngine2 {
#ifndef _DEBUG
#define _DEBUG 0
#endif

#ifdef _DEBUG
#define VSMAC_ASSERT(Expression)\
{\
assert(Expression);\
}
#else
#define VSMAC_ASSERT(Expression)
#endif

#define THREAD_CALLBACK __stdcall
    inline unsigned int SizeTypeToGUID32(USIZE_TYPE Size_Type)
    {
        return (Size_Type & 0xffffffff);
    }
    inline USIZE_TYPE GUID32ToSizeType(unsigned int uiGUID)
    {
#ifdef WINDOWS_PLATFORM
#if _WIN64
        return (uiGUID & 0x00000000ffffffff);
#else
        return (uiGUID & 0xffffffff);
#endif
#else
        static_assert(0, "No Implement!");;
#endif
    }
    inline int ComparePointer(void * Point1, void *Point2)
    {
#if WINDOWS_PLATFORM

        if (((USIZE_TYPE)Point1) == ((USIZE_TYPE)Point2))
        {
            return 0;
        }
        else if (((USIZE_TYPE)Point1) > ((USIZE_TYPE)Point2))
        {
            return 1;
        }
        else
        {
            return -1;
        }
#else
        static_assert(0, "No Implement!");;
#endif
    }

    class VSSYSTEM_API VSSystem
    {
    public:
        VSSystem();
        ~VSSystem();
        void text();
    };
}