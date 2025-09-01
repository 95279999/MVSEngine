# 设置可执行文件名和源文件
set(EXEC_NAME GameEngine)
set(SOURCES
        Private/main.cpp
        #Private/Engine.cpp
)

set(HEADERS
        #Public/Engine.h
)

# 创建可执行文件
add_executable(${EXEC_NAME} ${SOURCES} ${HEADERS})

# 设置包含目录
target_include_directories(${EXEC_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

# 链接所有引擎库
target_link_libraries(${EXEC_NAME}
        PRIVATE
        VSSystem
        #Graphics
        #Audio
        #Physics
        #UI
)

# 安装规则
install(TARGETS ${EXEC_NAME}
        RUNTIME DESTINATION bin
)