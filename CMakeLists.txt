cmake_minimum_required(VERSION 3.15)
project(Polygons)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/iterator.cpp
    src/loader.cpp
    src/output.cpp
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# Include Dir
include_directories(./include)

set(CMAKE_CXX_FLAGS "-O2")