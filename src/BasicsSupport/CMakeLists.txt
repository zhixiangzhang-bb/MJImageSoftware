# CMakeList.txt: BasicsSupport 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("zzx_BasicsSupport")



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)

#包含boost模块的头文件
include_directories(D:/Work/Clibrary/boost_1_83_0)

#包含taskflow模块的头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/taskflow)  


set(CMAKE_DEBUG_POSTFIX "d")


# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME} 
    BasicsSupport.cpp
    BasicsSupport.h
    threadpool.cpp
    threadpool.h
)





add_compile_definitions(${PROJECT_NAME})



target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
