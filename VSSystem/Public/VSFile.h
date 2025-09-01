//
// Created by lix on 2025/9/1.
//

#ifndef MVSENGINE_VSFILE_H
#define MVSENGINE_VSFILE_H
#include "VSSystem.h"
namespace VSEngine2 {

    class VSSYSTEM_API VSFile {
        public:
            enum class EOpenMode{
                RB,
                WB,
                RT,
                WT,
                MAX
            };
            enum class EPath {
                VSMAX_PATH = 256
            };
            enum class ESeekFlag {
                SF_CUR,
                SF_END,
                SF_SET,
                SF_MAX
            };
           VSFile();
           ~VSFile();
        bool Flush();  // 刷新文件缓冲区

        bool Seek(unsigned int uiOffset, unsigned int uiOrigin);  // 文件定位
        bool Open(const TCHAR * pFileName, EOpenMode uiOpenMode);  // 打开文件
        bool Write(const void *pBuffer, unsigned int uiSize, unsigned int uiCount);  // 写入数据
        bool Read(void *pBuffer, unsigned int uiSize, unsigned int uiCount);  // 读取数据

        // 读取一行文本到pBuffer中，如果buffer大小不够，读取的字符串最后一个字符是回车
        // 后面跟着2个字符：LF (Line Feed) - 换行符
        bool GetLine(void * pBuffer, unsigned int uiSize);

        // 获取文件大小
        inline unsigned int GetFileSize()const
        {
            return m_uiFileSize;
        }

        // 静态方法：检查文件是否存在
        static bool IsFileExists(const TCHAR * pFileName);
    protected:
        static TCHAR ms_cOpenMode[OM_MAX][5];
        static unsigned int m_uiSeekFlag[];
        FILE  *m_pFileHandle;
        unsigned int m_uiOpenMode;
        unsigned int m_uiFileSize;
        TCHAR m_tcFileName[EPath::VSMAX_PATH];
    };
}


#endif //MVSENGINE_VSFILE_H