cmake_minimum_required(VERSION 3.10)

project(DPDrawing)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
file(GLOB SOURCES
	classes/*.h
	classes/*.cpp
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})
include_directories("classes/")

add_executable(DPDrawing WIN32 main.cpp ${SOURCES})
target_link_libraries(DPDrawing ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
