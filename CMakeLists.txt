cmake_minimum_required( VERSION 4.00)

project(MVSEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置构建类型
if(NOT CMAKE_BUILD_TYPE)
 set(CMAKE_BUILD_TYPE Release)
endif()

# 添加子目录 - 顺序很重要，依赖关系需要先构建
#add_subdirectory(ThirdParty)
add_subdirectory(VSSystem)
#add_subdirectory(Graphics)
#add_subdirectory(Audio)
#add_subdirectory(Physics)
#add_subdirectory(UI)
add_subdirectory(Application)

#include_directories("Application/Public") # 头文件目录

#link_directories("/usr/local/lib/") # 链接库目录
# 收集当前目录下的所有源文件到SRCS变量
#aux_source_directory(. SRCS)
# 收集./abc目录下的所有源文件，追加到SRCS变量
#aux_source_directory(Application/Private SRCS)

#add_executable(${PROJECT_NAME} ${SRCS}
#        VSSystem/VSSystemExports.h)

# 可选：如果需要链接外部库，添加以下命令
# target_link_libraries(${PROJECT_NAME} PRIVATE 库名称)

# 可选：指定输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)