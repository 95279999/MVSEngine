//
// Created by lix on 2025/9/1.
//

#include "../Public/VSFile.h"
using namespace VSEngine2;

VSFile::VSFile() {
    m_pFileHandle = nullptr;
    m_uiOpenMode = OM_MAX;
    m_uiFileSize = 0;
}

VSFile::~VSFile() {
    if (m_pFileHandle)
    {
        fclose(m_pFileHandle);
        m_pFileHandle = nullptr;
    }
}

bool VSFile::Flush() {
    return(fflush(m_pFileHandle) == 0);
}

bool VSFile::Seek(unsigned int uiOffset, unsigned int uiOrigin) {
    VSMAC_ASSERT(m_pFileHandle);
    fseek(m_pFileHandle,uiOffset,uiOrigin);
    return true;
}

bool VSFile::Open(const TCHAR *pFileName, unsigned int uiOpenMode) {
    if (m_pFileHandle)
    {
        fclose(m_pFileHandle);
    }
    VSMAC_ASSERT(!m_pFileHandle);
    VSMAC_ASSERT(uiOpenMode < OM_MAX);
    unsigned int uiLen = VSStrLen(pFileName);
    if (uiLen < VSMAX_PATH - 1)
    {
        if(!VSMemcpy(m_tcFileName,pFileName,uiLen + 1))
            return false;
    }
    else
    {
        return false;
    }

    m_uiOpenMode = uiOpenMode;
    if (m_uiOpenMode == OM_RB || m_uiOpenMode == OM_RT)
    {
        struct _stat64i32 kStat;
        if (_tstat(pFileName,&kStat) != 0)
        {
            return false;
        }
        m_uiFileSize = kStat.st_size;
    }

    errno_t uiError = _tfopen_s(&m_pFileHandle,pFileName,ms_cOpenMode[m_uiOpenMode]);
    if (uiError)
    {
        return 0;
    }
    if (!m_pFileHandle)
    {
        return 0;
    }

    return true;
}
