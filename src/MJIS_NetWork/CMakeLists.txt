# CMakeList.txt: DataProcess 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#固定编译器选项，这里用较新的C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MJIS_NetWork")





find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 COMPONENTS Network REQUIRED) 





#包含日志板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/glog/include)


set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")


# 将源代码添加到此项目的可执行文件。
add_library(${PROJECT_NAME} SHARED
	#DataCommumication.cpp 
	#DataCommumication.h
	DataConvert.h
	DataConvert.cpp
	#DataInterface.cpp 
	#DataInterface.h
	#DataInterface.ui
	#TCPSet.h
	#TCPSet.cpp
	#TCPSet.ui
	TCPConnect.h
	TCPConnect.cpp
	#DataSetInformation.h
	#DataSetInformation.cpp
	#DataSetInformation.ui
	mjis_network_global.h
	)




add_compile_definitions(${PROJECT_NAME})



target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network)

target_link_libraries(${PROJECT_NAME} PRIVATE   D:/Work/Clibrary/glog/lib/glog$<$<CONFIG:Debug>:d>.lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
