# 定义库名和源文件

set(LIB_NAME VSSystem)
set(SOURCES
        Private/VSSystem.cpp
        Private/VSFile.cpp
        #Private/MemoryManager.cpp
        #Private/Logger.cpp
        #Private/ConfigManager.cpp


)

set(HEADERS
        VSPlatform.h
        VSSystemExports.h
        Public/VSSystem.h
        Public/VSFile.h
        #Public/MemoryManager.h
        #Public/FileSystem.h
        #Public/Logger.h
        #Public/ConfigManager.h
)

# 创建动态库
add_library(${LIB_NAME} SHARED ${SOURCES} ${HEADERS})

# 设置导出宏
target_compile_definitions(${LIB_NAME}
        PRIVATE
        VSSYSTEM_EXPORTS  # 构建库时定义
        PUBLIC
        ENGINE_API=VSSYSTEM_API  # 使用库时定义
)

# 设置包含目录
target_include_directories(${LIB_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

# 设置库属性
#set_target_properties(${LIB_NAME} PROPERTIES
#        VERSION ${PROJECT_VERSION}
#        SOVERSION 1
#        DEBUG_POSTFIX "d"
#)

# 链接依赖
target_link_libraries(${LIB_NAME}
        PRIVATE
        #ThirdParty::SomeThirdPartyLib
)

# 安装规则
install(TARGETS ${LIB_NAME}
        EXPORT ${LIB_NAME}Targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include
)

install(DIRECTORY Public/ DESTINATION include
        FILES_MATCHING PATTERN "*.h"
)