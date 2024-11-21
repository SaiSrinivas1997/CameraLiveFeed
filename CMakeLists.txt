cmake_minimum_required(VERSION 3.10)
project(CameraApp)

# Specify the path to Qt6Config.cmake
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.8.0\\msvc2022_64\\lib\\cmake" ${CMAKE_PREFIX_PATH})
set(OpenCV_DIR "C:\\opencv\\build\\x64\\vc16\\lib")


# Find Qt and OpenCV packages
find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)
find_package(OpenCV REQUIRED)

# Set C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Add MSVC specific compile options
if(MSVC)
    add_compile_options(/Zc:__cplusplus /std:c++17 /permissive)
endif()

# Generate MOC files
qt6_wrap_cpp(CameraApp_moc CameraApp.h)

# Add your source files here
add_executable(CameraApp main.cpp CameraApp.cpp)
target_sources(CameraApp PRIVATE ${CameraApp_moc})

# Link the libraries
target_link_libraries(CameraApp Qt6::Core Qt6::Widgets ${OpenCV_LIBS})

include_directories(${Qt6Widgets_INCLUDE_DIRS} ${Qt6Core_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

