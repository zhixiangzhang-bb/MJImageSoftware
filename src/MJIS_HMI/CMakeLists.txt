# CMakeList.txt: MJIS_HMI 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#固定编译器选项，这里用较新的C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MJIS_HMI")


find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 COMPONENTS PrintSupport REQUIRED) 
find_package(Qt6 COMPONENTS Network REQUIRED) 





#包含自身头文件
include_directories(${CMAKE_SOURCE_DIR}/src/MJIS_HMI/include)
#包含相机模块头文件
include_directories(${CMAKE_SOURCE_DIR}/src/MJIS_Camera)
#包含数据处理头文件
include_directories(${CMAKE_SOURCE_DIR}/src/MJIS_NetWork)
#包含OpenCV库板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/opencv/include)
#包含日志板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/glog/include)
#包含相机头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/mvcamera)
#包含自定义库中的视觉板块
include_directories(D:/MJLib/src/MJLib_Vision)



set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")



#设置项目源文件
set(PROJECT_SOURCES
	src/MJIS_HMI.cpp  
	src/mjis_chartwidget.cpp
	src/qcustomplot.cpp
	src/mjis_aboutme.cpp
	src/mjis_localcameraui.cpp
	src/mjis_networkcamera.cpp
	src/mjis_systemmessage.cpp
	src/mjis_tabwidget.cpp
	src/mjis_videopathset.cpp
	src/mjis_datainterface.cpp
	src/mjis_tcpset.cpp
	src/mjis_datasetinformation.cpp
	src/mjis_configui.cpp
	src/mjis_dockvideo.cpp
	src/mjis_processinginterface.cpp
)


#设置项目头文件
set(PROJECT_HEADER
	include/mjis_hmi_global.h
	include/mjis_hmi_api.h
	include/MJIS_HMI.h  
	include/mjis_chartwidget.h
	include/qcustomplot.h
	include/mjis_aboutme.h
	include/mjis_localcameraui.h
	include/mjis_networkcamera.h
	include/mjis_systemmessage.h
	include/mjis_tabwidget.h
	include/mjis_videopathset.h
	include/mjis_datainterface.h
	include/mjis_tcpset.h
	include/mjis_datasetinformation.h
	include/mjis_configui.h
	include/mjis_dockvideo.h
	include/mjis_processinginterface.h

)



#设置项目UI文件
set(PROJECT_UI
	src/mjis_chartwidget.ui
	src/mjis_aboutme.ui
	src/mjis_localcameraui.ui
	src/mjis_networkcamera.ui
	src/mjis_systemmessage.ui
	src/mjis_tabwidget.ui
	src/mjis_videopathset.ui
	src/mjis_datainterface.ui
	src/mjis_tcpset.ui
	src/mjis_datasetinformation.ui
	src/mean.ui
    src/binaryimageui.ui
    src/gaussian.ui
    src/median.ui
    src/Bilateral.ui
	src/mjis_dockvideo.ui
	src/mjis_processinginterface.ui
)

	
# 将源代码添加到此项目的共享库。
add_library (${PROJECT_NAME} SHARED
	${PROJECT_SOURCES}
	${PROJECT_HEADER}
	${PROJECT_UI}
)


#添加项目名称宏
add_compile_definitions(${PROJECT_NAME})


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


target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::PrintSupport)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network)


#链接库
target_link_libraries(${PROJECT_NAME} PRIVATE  MJIS_Camera MJIS_NetWork)
target_link_libraries(${PROJECT_NAME} PRIVATE  D:/Work/Clibrary/glog/lib/glog$<$<CONFIG:Debug>:d>.lib)


#链接自定义库
target_link_libraries(${PROJECT_NAME} PRIVATE  
    D:/MJLib/out/build/x64/src/MJLib_Vision/Debug/MJLib_Visiond.lib
    D:/MJLib/out/build/x64/src/MJLib_Camera/Debug/MJLib_Camerad.lib
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
