//
// Created by lix on 2025/9/3.
//

#ifndef MVSENGINE_VSSINGLETON_H
#define MVSENGINE_VSSINGLETON_H
#include "VSSystem.h"
namespace VSEngine2
{

    template <typename T>
    class  VSSingleton
    {
        static T *m_pSingleton;

    public:
        VSSingleton()
        {
            VSMAC_ASSERT( !m_pSingleton );
            m_pSingleton = static_cast<T*>(this);
        }

        ~VSSingleton()
        {
            VSMAC_ASSERT( m_pSingleton );
            m_pSingleton = NULL;
        }

        static T &GetSingleton()
        {
            VSMAC_ASSERT( m_pSingleton );
            return (*m_pSingleton);
        }

        static T *GetSingletonPtr()
        {
            return (m_pSingleton);
        }
    };

    template <typename T> T *VSSingleton<T>::m_pSingleton = NULL;

}
#endif //MVSENGINE_VSSINGLETON_H