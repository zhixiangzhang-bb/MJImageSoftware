cmake_minimum_required(VERSION 3.5)

project(MJIS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 COMPONENTS Network REQUIRED) 


#添加库
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BasicsSupport)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJIS_Camera)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJIS_ImageProcess)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/DataProcess)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJIS_MachineLearning)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJIS_Agent)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/NeuralNetwork)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJIS_HMI)


#设置opencv库
#set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/3rdparty/opencv/)
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS}) 
#link_directories(${OpenCV_LIBRARY_DIRS})
#add_definitions(${OpenCV_LIBRARY_DIRS})E:\Work\Clibrary\boost_1_83_0



#包含boost模块的头文件
#include_directories(D:/Work/Clibrary/boost_1_83_0)



#包含ads模块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/abs/include)
#包含SARibbon模块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/SARibbon/include)
#包含OpenCV库板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/opencv/include)
#包含日志板块的头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/glog/include)
#包含图像处理板块头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/MJIS_ImageProcess)
#包含日志模块的头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/LogHandler)
#包含HMI模块头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/MJIS_HMI)
#包含数据处理头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/DataProcess)
#包含机器学习头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/MJIS_MachineLearning)
#包含代理头文件
include_directories(${CMAKE_SOURCE_DIR}/src/MJIS_Agent)
#包含任务流头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/3rdparty/taskflow)
#包含相机头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/mvcamera)


#包含自定义库中的视觉板块
include_directories(D:/MJLib/src/MJLib_Vision)



#openvino
include_directories(D:/Work/Clibrary/openvino/include/ie)
include_directories(D:/Work/Clibrary/openvino/include/ngraph)
include_directories(D:/Work/Clibrary/openvino/include/openvino)



set(TS_FILES MJImageSoft_zh_CN.ts)



#设置项目文件
set(PROJECT_SOURCES
        src/main.cpp
        src/Control/presenter.h
        src/Control/presenter.cpp
        src/Control/cameraagent.h
        src/Control/cameraagent.cpp
        src/Control/mainwindow.cpp
        src/Control/mainwindow.h
        src/Control/mainwindow.ui
        src/Control/videopathset.h
        src/Control/videopathset.cpp
        src/Control/videopathset.ui
        src/LogHandler/SystemMessage.h
        src/LogHandler/SystemMessage.cpp
        src/LogHandler/SystemMessage.ui
        src/LogHandler/loghead.h
        Icon.qrc
        ${TS_FILES}
)



#设置UI文件
set(UI_SOURCES
        Icon.qrc
)




if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${UI_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
            ${UI_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
            ${UI_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()




target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network)




#target_link_libraries(${PROJECT_NAME}  PRIVATE 
#   D:/Work/Clibrary/CUDA/v12.2/lib/x64/cudart_static.lib
#   D:/ZImageSoft/CavitationAPP/src/3rdparty/opencv/lib/opencv_core470$<$<CONFIG:Debug>:d>.lib
#   D:/ZImageSoft/CavitationAPP/src/3rdparty/opencv/lib/opencv_highgui470$<$<CONFIG:Debug>:d>.lib
#   D:/ZImageSoft/CavitationAPP/src/3rdparty/opencv/lib/opencv_imgproc470$<$<CONFIG:Debug>:d>.lib
#   D:/ZImageSoft/CavitationAPP/src/3rdparty/opencv/lib/opencv_videoio470$<$<CONFIG:Debug>:d>.lib
#  D:/ZImageSoft/CavitationAPP/src/3rdparty/opencv/lib/opencv_imgcodecs470$<$<CONFIG:Debug>:d>.lib
#   D:/ZImageSoft/CavitationAPP/src/3rdparty/opencv/lib/opencv_ml470$<$<CONFIG:Debug>:d>.lib
#   D:/Work/Clibrary/opencv/install/x64/vc17/lib/opencv_dnn470$<$<CONFIG:Debug>:d>.lib
#   D:/Work/Clibrary/opencv/install/x64/vc17/lib/opencv_dnn_objdetect470$<$<CONFIG:Debug>:d>.lib
#)



#target_link_libraries(${PROJECT_NAME}  PRIVATE 
#   D:/Work/Clibrary/openvino/lib/openvino.lib
#)






#链接图形界面布局库
target_link_libraries(${PROJECT_NAME}  PRIVATE 
                        ${CMAKE_SOURCE_DIR}/3rdparty/abs/lib/qt6advanceddocking$<$<CONFIG:Debug>:d>.lib
                        ${CMAKE_SOURCE_DIR}/3rdparty/SARibbon/lib/SARibbonBar$<$<CONFIG:Debug>:d>.lib
                        )






#链接库
target_link_libraries(${PROJECT_NAME} PRIVATE  MJIS_ImageProcess MJIS_Agent MJIS_HMI MJIS_MachineLearning zzxlib_DataProcess)
target_link_libraries(${PROJECT_NAME} PRIVATE  D:/Work/Clibrary/glog/lib/glog$<$<CONFIG:Debug>:d>.lib)



#链接自定义库
target_link_libraries(${PROJECT_NAME} PRIVATE  
    D:/MJLib/out/build/x64/src/MJLib_Vision/Debug/MJLib_Visiond.lib
)





set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

