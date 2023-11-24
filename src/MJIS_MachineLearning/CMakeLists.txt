# CMakeList.txt: MachineLearning 的 CMake 项目，在此处包括源代码并定义
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

project ("MJIS_MachineLearning")


find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(CUDA REQUIRED)



# 将源代码添加到此项目的可执行文件。
#add_executable (MachieLnearning "MachieLnearning.cpp" "MachieLnearning.h")

#包含OpenCV库板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/opencv/include)

#包含taskflow库板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/taskflow)

#包含图表库板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/src/MJIS_HMI/include)
#包含自定义库中的视觉板块
include_directories(D:/MJLib/src/MJLib_Vision)


set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

# 生成库
add_library (${PROJECT_NAME} SHARED
	machinelearning.h
	configinterface.h
	configinterface.cpp
	configinterface.ui
	RandomForest.h
	RandomForest.cpp
	randomforestconfig.h
	randomforestconfig.cpp
	randomforestconfig.ui
	neuralnetwork.h
	neuralnetwork.cpp
	datapreprocessing.h
	datapreprocessing.cpp
	#Test.cpp
	)



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
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/opencv_dnn470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv/install/x64/vc17/staticlib/opencv_ml470$<$<CONFIG:Debug>:d>.lib
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
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/opencv_dnn470$<$<CONFIG:Debug>:d>.lib
	D:/Work/Clibrary/opencv_x86/install/x86/vc17/staticlib/opencv_ml470$<$<CONFIG:Debug>:d>.lib
	)

endif()



#PyTorch系列库
target_link_libraries(${PROJECT_NAME}  PRIVATE 
   D:/Work/Clibrary/libtorch/lib/c10.lib
   D:/Work/Clibrary/libtorch/lib/c10_cuda.lib
   D:/Work/Clibrary/libtorch/lib/torch_cpu.lib
   D:/Work/Clibrary/libtorch/lib/torch_cuda.lib
)



target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE  MJIS_HMI)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
