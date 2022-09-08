cmake_minimum_required(VERSION 2.8)
project(handwritten_slam)
#编译设置
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()
# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   add_definitions(-DCOMPILEDWITHC11)
   message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
   add_definitions(-DCOMPILEDWITHC0X)
   message(STATUS "Using flag -std=c++0x.")
else()
   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
#第三方库支持
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

#找本地的库
find_package(OpenCV 3.2 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Pangolin REQUIRED)
find_package(Sophus REQUIRED)
find_package(FMT REQUIRED)
#添加文件地址
include_directories(
   ${PROJECT_SOURCE_DIR}
   #./include/handwritten_slam
   ${PROJECT_SOURCE_DIR}/include/handwritten_slam
   ${EIGEN3_INCLUDE_DIR}
   ${Pangolin_INCLUDE_DIRS}
   ${Sophus_INCLUDE_DIRS}
)
#输出库文件
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
#输出二进制执行文件
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#创建共享库
#原本这里有个SHARE 但是会报错，这是由于动态库和静态库不能混用
#TODO:静态库和动态库的区别
add_library( ${PROJECT_NAME} 
#cpp文件
#h文件
src/camera.cpp
src/Frame.cpp
src/Map.cpp
src/MapPoint.cpp
include/handwritten_slam/camera.h
include/handwritten_slam/common_include.h
include/handwritten_slam/Frame.h
include/handwritten_slam/Map.h
include/handwritten_slam/MapPoint.h
include/handwritten_slam/config.h

)

#创建可执行文件
#add_executable(camera src/camera.cpp)   没有main函数 不用创建可执行文件，只创建有main函数的
target_link_libraries(
${PROJECT_NAME}
${OpenCV_LIBS}
${EIGEN3_LIBS}
${Pangolin_LIBRARIES}
${Sophus_LIBRARIES}
fmt::fmt
)
#target_link_libraries(camera ${PROJECT_NAME})