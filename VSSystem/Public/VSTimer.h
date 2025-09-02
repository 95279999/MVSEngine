//
// Created by lix on 2025/9/2.
//

#ifndef MVSENGINE_VSTIMER_H
#define MVSENGINE_VSTIMER_H
#include "../Public/VSSystem.h"
namespace VSEngine2 {
   class VSTimer {
   private:
      bool m_bUseLargeTime{};
      __int64 m_int64OneSecondTicks{};
      __int64 m_int64TimeTickStartCounts{};
      unsigned long m_ulTimeStart{};
      int m_iFrameCount{};
      double m_fFPS{};
      double m_fTime{},m_fLastFPSTime{},m_fTimeSlice{};
      double m_fDetTime{},m_fLastTime{};
      void InitGameTime();
   public:
      VSTimer();
      ~VSTimer();

      double GetGamePlayTime();
      void UpdateFPS();
      inline double GetFPS() { return m_fFPS; }
      static VSTimer* ms_pTimer;
      double GetDetTime() {return m_fDetTime;}
      int GetRandSeed();
   };
}



#endif //MVSENGINE_VSTIMER_H