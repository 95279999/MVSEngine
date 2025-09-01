//
// Created by lix on 2025/9/1.
//

#ifndef MVSENGINE_VSSYSTEM_H
#define MVSENGINE_VSSYSTEM_H
// 平台检测
#if defined(_WIN32)
    #ifdef VSSYSTEM_EXPORTS
        #define VSSYSTEM_API __declspec(dllexport)
    #else
        #define VSSYSTEM_API __declspec(dllimport)
    #endif
#else
    #define VSSYSTEM_API __attribute__((visibility("default")))
#endif
#endif //MVSENGINE_VSSYSTEM_H