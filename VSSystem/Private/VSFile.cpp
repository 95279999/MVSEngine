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
