# CMakeList.txt: Agent 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)



set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


project ("MJIS_Agent")


find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

#包含图像处理板块
include_directories(${CMAKE_SOURCE_DIR}/src/MJIS_ImageProcess)
#包含相机板块
#include_directories(${CMAKE_SOURCE_DIR}/src/MJIS_Camera)


#包含日志板块的头文件
#include_directories(${CMAKE_SOURCE_DIR}/src/Image)

#包含OpenCV库板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/opencv/include)

#包含相机头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/mvcamera)

#包含自定义库
include_directories(D:/MJLib/src/MJLib_Vision)


set(CMAKE_DEBUG_POSTFIX "d")


# 将源代码添加到此项目的可执行文件。
add_library (${PROJECT_NAME} SHARED
			mjis_agent.cpp 
			mjis_agent.h
			mjis_imageagent.cpp
			mjis_imageagent.h
			mjis_tabwidget.cpp
			mjis_tabwidget.h
			mjis_tabwidget.ui
			mjis_localcameraui.cpp
			mjis_localcameraui.h
			mjis_localcameraui.ui
			mjis_networkcamera.cpp
			mjis_networkcamera.h
			mjis_networkcamera.ui
			mjis_agent_api.h
			mjis_agent_macro.h
			mjis_camera.cpp
			mjis_camera.h
)


add_compile_definitions(${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME} PRIVATE  Qt${QT_VERSION_MAJOR}::Widgets)


target_link_libraries(${PROJECT_NAME} PRIVATE  MJIS_ImageProcess)
#target_link_libraries(${PROJECT_NAME} PRIVATE  MJIS_Camera)



#判断编译器位数执行不同链接操作
if(CMAKE_CL_64)    
target_link_libraries(${PROJECT_NAME}  PRIVATE 
	D:/Work/Clibrary/CUDA/v12.2/lib/x64/cudart_static.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/ittnotify$<$<CONFIG:Debug>:d>.lib	
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/zlib$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/ippicvmt.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/ippiw$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/ittnotify$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/opencv_core470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/opencv_imgproc470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/opencv_imgcodecs470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/opencv_highgui470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/libprotobuf$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/libpng$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/libopenjp2$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/libjpeg-turbo$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/libwebp$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/libtiff$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/IlmImf$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/opencv_videoio470$<$<CONFIG:Debug>:d>.lib
)


else()
	target_link_libraries(${PROJECT_NAME}  PRIVATE 
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/ittnotify$<$<CONFIG:Debug>:d>.lib	
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/zlib$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/opencv_core470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/opencv_imgproc470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/opencv_imgcodecs470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/opencv_highgui470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/libprotobuf$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/libpng$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/libopenjp2$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/libjpeg-turbo$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/libwebp$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/libtiff$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/IlmImf$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/opencv_videoio470$<$<CONFIG:Debug>:d>.lib
)

endif()





#target_link_libraries(${PROJECT_NAME}  PRIVATE 
#   ${CMAKE_SOURCE_DIR}/3rdparty/opencv/lib/opencv_core470$<$<CONFIG:Debug>:d>.lib
#   ${CMAKE_SOURCE_DIR}/3rdparty/opencv/lib/opencv_highgui470$<$<CONFIG:Debug>:d>.lib
#   ${CMAKE_SOURCE_DIR}/3rdparty/opencv/lib/opencv_imgproc470$<$<CONFIG:Debug>:d>.lib
#   ${CMAKE_SOURCE_DIR}/3rdparty/opencv/lib/opencv_videoio470$<$<CONFIG:Debug>:d>.lib
#   ${CMAKE_SOURCE_DIR}/3rdparty/opencv/lib/opencv_imgcodecs470$<$<CONFIG:Debug>:d>.lib
#   ${CMAKE_SOURCE_DIR}/3rdparty/opencv/lib/opencv_features2d470$<$<CONFIG:Debug>:d>.lib
#   ${CMAKE_SOURCE_DIR}/3rdparty/opencv/lib/opencv_xfeatures2d470$<$<CONFIG:Debug>:d>.lib
#   ${CMAKE_SOURCE_DIR}/3rdparty/opencv/lib/opencv_freetype470$<$<CONFIG:Debug>:d>.lib
#)


#链接自定义库
target_link_libraries(${PROJECT_NAME} PRIVATE  
    D:/MJLib/out/build/x64/src/MJLib_Vision/Debug/MJLib_Visiond.lib
    D:/MJLib/out/build/x64/src/MJLib_Camera/Debug/MJLib_Camerad.lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE  
    D:/Work/Clibrary/MTD/mvcamera/MVCamProptySheet.lib
    D:/Work/Clibrary/MTD/mvcamera/MVGigE.lib
    D:/Work/Clibrary/MTD/mvcamera/MVTickDlg.lib    
)



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
