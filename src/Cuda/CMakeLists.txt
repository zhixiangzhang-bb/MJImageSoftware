# CMakeList.txt: Cuda 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)






# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Cuda" LANGUAGES CXX CUDA)


enable_language(CUDA)


#包含cuda模块头文件
include_directories(E:/Work/Clibrary/CUDA/v12.2/include)


#包含cudnn模块头文件
include_directories(E:/Work/Clibrary/cuDNN/include)




# 将源代码添加到此项目的可执行文件。
add_executable (Cuda 
	Test.cu
	CUDARandom.cuh
	CUDARandom.cu)





target_link_libraries(${PROJECT_NAME}  PRIVATE E:/Work/Clibrary/CUDA/v12.2/lib/x64/cudart_static.lib)


target_link_libraries(${PROJECT_NAME}  PRIVATE 
	E:/Work/Clibrary/cuDNN/lib/x64/cudnn.lib
	E:/Work/Clibrary/cuDNN/lib/x64/cudnn_ops_infer.lib
	E:/Work/Clibrary/cuDNN/lib/x64/cudnn_cnn_infer64_8.lib
	)




# TODO: 如有需要，请添加测试并安装目标。
