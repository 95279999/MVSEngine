//
// Created by lix on 2025/9/2.
//

#include "../Public/VSTimer.h"
#include <MMSystem.h>
using namespace VSEngine2;
VSTimer* VSTimer::ms_pTimer = nullptr;
void VSEngine2::VSTimer::InitGameTime() {
    m_iFrameCount = 0;
    m_fFPS = 0;
    m_fTime = 0;
    m_fLastFPSTime = 0;
    m_fTimeSlice = 0;
    m_fLastTime = 0;
    m_fDetTime = 0;
    if(QueryPerformanceFrequency((LARGE_INTEGER*) &m_int64OneSecondTicks))
    {
        m_bUseLargeTime=true;
        QueryPerformanceCounter((LARGE_INTEGER*) &m_int64TimeTickStartCounts);
    }
    else
    {
        m_bUseLargeTime = false;
        m_ulTimeStart = timeGetTime();
    }
}

VSTimer::VSTimer() {
    InitGameTime();
    ms_pTimer = this;
}

VSTimer::~VSTimer() {
}

double VSTimer::GetGamePlayTime() {
    __int64 int64TimeCurrentCounts;
    if(m_bUseLargeTime)
    {
        QueryPerformanceCounter((LARGE_INTEGER*) &int64TimeCurrentCounts);
        return ((int64TimeCurrentCounts - m_int64TimeTickStartCounts)*(1.0 / m_int64OneSecondTicks)*1000.0);
    }
    else
    {
        return ((timeGetTime() - m_ulTimeStart));
    }
}

void VSTimer::UpdateFPS() {
    // 1. 获取当前游戏时间（毫秒转秒，方便计算1秒周期）
    m_fTime = GetGamePlayTime() * 0.001;
    // 2. 计算“当前帧与上一帧的时间差”（m_fDetTime：帧间隔，秒）
    m_fDetTime = m_fTime - m_fLastTime;
    // 3. 更新“上一帧时间”，为下一帧计算间隔做准备
    m_fLastTime = m_fTime;

    // 4. 每1秒计算一次帧率
    if (m_fTime - m_fLastFPSTime > 1.0f)
    {
        m_fLastFPSTime = m_fTime;  // 更新“上一次计算FPS的时间”
        m_fFPS = m_iFrameCount;    // 过去1秒的帧计数 → 帧率（FPS）
        m_iFrameCount = 0;         // 重置帧计数器，开始下1秒统计
    }
    else
    {
        m_iFrameCount++;  // 未到1秒，帧计数器+1（每调用一次代表1帧）
    }
}

int VSTimer::GetRandSeed() {
    return ((LARGE_INTEGER*)&m_int64TimeTickStartCounts)->LowPart;
}
