# CMakeList.txt: Image 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)




# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


project ("MJIS_ImageProcess")    



#set(OpenCV_DIR E:/Work/C++/opencv4.7.0build/install)
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS}) 
#link_directories(${OpenCV_LIBRARY_DIRS})
#add_definitions(${OpenCV_LIBRARY_DIRS})


#包含OpenCV库板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/opencv/include)
#包含维视相机头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/mvcamera)

#包含自定义库中的视觉板块
include_directories(D:/MJLib/src/MJLib_Vision)

#包含日志板块的头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/glog/include)


find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)



set(CMAKE_DEBUG_POSTFIX "d")




add_library(${PROJECT_NAME} SHARED
        mjis_imageprocess_api.h
        mjis_imageprocess_macro.h
        mjis_dockvideo.h
        mjis_dockvideo.cpp
        mjis_dockvideo.ui
        mjis_imagelibconnect.h
        mjis_imagelibconnect.cpp
        mjis_processinginterface.h
        mjis_processinginterface.cpp
        mjis_processinginterface.ui
        mjis_configui.h
        mjis_configui.cpp
        mean.ui
        binaryimageui.ui
        gaussian.ui
        median.ui
        Bilateral.ui
)




add_compile_definitions(${PROJECT_NAME})


#链接自定义库
target_link_libraries(${PROJECT_NAME} PRIVATE  
    D:/MJLib/out/build/x64/src/MJLib_Vision/Debug/MJLib_Visiond.lib
    D:/MJLib/out/build/x64/src/MJLib_Camera/Debug/MJLib_Camerad.lib
)




target_link_libraries(${PROJECT_NAME} PRIVATE  Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE  D:/Work/Clibrary/glog/lib/glog$<$<CONFIG:Debug>:d>.lib)



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
