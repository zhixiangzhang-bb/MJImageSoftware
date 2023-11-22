# CMakeList.txt: MachineLearning 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)





# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("lib_CNN")




# 将源代码添加到此项目的可执行文件。
#add_executable (MachieLnearning "MachieLnearning.cpp" "MachieLnearning.h")



#包含OpenCV库板块的头文件
include_directories(D:/Work/Clibrary/opencv32/install/include)

#包含taskflow库板块的头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/taskflow)


			

set(CMAKE_DEBUG_POSTFIX "d")



# 生成库
add_library (${PROJECT_NAME} SHARED
	neuralnetwork.h
	neuralnetwork.cpp
	CNN.h
	CNN.cpp
	Test.cpp
	)



add_compile_definitions(${PROJECT_NAME})



#OPENCV系列库
target_link_libraries(${PROJECT_NAME}  PRIVATE 
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/ittnotify$<$<CONFIG:Debug>:d>.lib	
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/zlib$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/opencv_core470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/opencv_imgproc470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/opencv_imgcodecs470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/opencv_highgui470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/opencv_dnn470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/libprotobuf$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/libpng$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/libopenjp2$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/libjpeg-turbo$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/libwebp$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/libtiff$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv32/install/x86/vc17/staticlib/IlmImf$<$<CONFIG:Debug>:d>.lib
)
##



#target_link_libraries(${PROJECT_NAME}  PRIVATE 
#	D:/Work/Clibrary/opencv32/install/x86/vc17/lib/opencv_core470$<$<CONFIG:Debug>:d>.lib
#	D:/Work/Clibrary/opencv32/install/x86/vc17/lib/opencv_imgproc470$<$<CONFIG:Debug>:d>.lib
#	D:/Work/Clibrary/opencv32/install/x86/vc17/lib/opencv_dnn470$<$<CONFIG:Debug>:d>.lib
#)



#OPENCV系列库
target_link_libraries(${PROJECT_NAME}  PRIVATE 
	D:/Work/Clibrary/CUDA/v12.2/lib/x64/cudart_static.lib

)





if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
