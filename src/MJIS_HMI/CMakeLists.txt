# CMakeList.txt: MJIS_HMI 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MJIS_HMI")


find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 COMPONENTS PrintSupport REQUIRED) 



# 将源代码添加到此项目的可执行文件。
add_library (${PROJECT_NAME} SHARED
	MJIS_HMI.cpp 
	MJIS_HMI.h
	mjis_hmi_global.h
	mjis_hmi_api.h
	mjis_chartwidget.cpp
	mjis_chartwidget.h
	mjis_chartwidget.ui
	qcustomplot.h
	qcustomplot.cpp
	mjis_aboutme.h
	mjis_aboutme.cpp
	mjis_aboutme.ui
)



#添加项目名称宏
add_compile_definitions(${PROJECT_NAME})



target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::PrintSupport)



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
