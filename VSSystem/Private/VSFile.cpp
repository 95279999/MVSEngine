//
// Created by lix on 2025/9/1.
//

#include "../Public/VSFile.h"
using namespace VSEngine2;
TCHAR VSFile::ms_cOpenMode[OM_MAX][5] =
{
    _T("rb"),
    _T("wb"),
    _T("rt"),
    _T("wt"),
};
unsigned int VSFile::m_uiSeekFlag[] =
{
    SEEK_CUR,
    SEEK_END,
    SEEK_SET
};
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

bool VSFile::Open(const TCHAR *pFileName, unsigned int uiOpenMode)
{
    // 如果已有打开的文件，先关闭
    if (m_pFileHandle)
    {
        fclose(m_pFileHandle);
        m_pFileHandle = nullptr; // 确保指针被重置
    }

    VSMAC_ASSERT(!m_pFileHandle);
    VSMAC_ASSERT(uiOpenMode < OM_MAX);

    // 检查文件名长度
    unsigned int uiLen = _tcslen(pFileName);
    if (uiLen >= VSMAX_PATH - 1)
    {
        return false; // 文件名太长
    }

    // 复制文件名 - 修复VSMemcpy使用方式
    // VSMemcpy需要目标缓冲区大小作为最后一个参数
    if(!VSMemcpy(m_tcFileName, pFileName, (uiLen + 1) * sizeof(TCHAR), sizeof(m_tcFileName)))
    {
        return false;
    }

    m_uiOpenMode = uiOpenMode;

    // 如果是读模式，获取文件大小
    if (m_uiOpenMode == OM_RB || m_uiOpenMode == OM_RT)
    {
        struct _stat statInfo;
        if (_tstat(pFileName, &statInfo) != 0)
        {
            return false; // 获取文件信息失败
        }
        m_uiFileSize = statInfo.st_size;
    }
    else
    {
        m_uiFileSize = 0; // 写模式下文件大小初始为0
    }

    // 打开文件
    errno_t err = _tfopen_s(&m_pFileHandle, pFileName, ms_cOpenMode[m_uiOpenMode]);
    if (err != 0 || !m_pFileHandle)
    {
        // 打开失败，重置状态
        m_pFileHandle = nullptr;
        m_uiOpenMode = OM_MAX;
        m_uiFileSize = 0;
        m_tcFileName[0] = _T('\0');
        return false;
    }

    return true;
}
