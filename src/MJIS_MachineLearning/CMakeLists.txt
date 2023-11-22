# CMakeList.txt: MachineLearning 的 CMake 项目，在此处包括源代码并定义
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
include_directories(${CMAKE_SOURCE_DIR}/src/MJIS_HMI)



set(CMAKE_DEBUG_POSTFIX "d")



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


#OPENCV系列库
target_link_libraries(${PROJECT_NAME}  PRIVATE 
   D:/Work/Clibrary/opencv/install/x64/vc17/lib/opencv_core470$<$<CONFIG:Debug>:d>.lib
   D:/Work/Clibrary/opencv/install/x64/vc17/lib/opencv_imgcodecs470$<$<CONFIG:Debug>:d>.lib
   D:/Work/Clibrary/opencv/install/x64/vc17/lib/opencv_ml470$<$<CONFIG:Debug>:d>.lib
   D:/Work/Clibrary/opencv/install/x64/vc17/lib/opencv_imgproc470$<$<CONFIG:Debug>:d>.lib
   D:/Work/Clibrary/opencv/install/x64/vc17/lib/opencv_highgui470$<$<CONFIG:Debug>:d>.lib
   D:/Work/Clibrary/opencv/install/x64/vc17/lib/opencv_dnn470$<$<CONFIG:Debug>:d>.lib
)


#CUDA系列库
target_link_libraries(${PROJECT_NAME}  PRIVATE  
	#E:/NVIDIAGPU/CUDA/lib/x64/cudart_static.lib
	#E:/NVIDIA GPU/CUDA/lib/x64/cudnn.lib
	)


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
