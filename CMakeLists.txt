cmake_minimum_required(VERSION 3.0.0)
project(improc VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
#set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)


find_package(CUDA REQUIRED)
message(STATUS "CUDA Inc:")
message(STATUS ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${INCLUDE_DIR} ${CUDA_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main_program.cpp)
add_subdirectory(src)

target_link_libraries( 
    ${PROJECT_NAME} 
    PUBLIC ${OpenCV_LIBS} ${CUDA_LIBRARIES}
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#include(CTest)
#enable_testing()
#add_subdirectory(${TEST_DIR})