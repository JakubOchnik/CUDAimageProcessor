add_executable(${PROJECT_NAME} main.cpp)

find_package(CUDA REQUIRED)

find_package(OpenCV REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS} ${INCLUDE_DIR} ${CUDA_INCLUDE_DIRS})

if(UNIX)
    find_package(X11 REQUIRED)
endif(UNIX)

target_link_libraries( 
    ${PROJECT_NAME} 
    PUBLIC ${OpenCV_LIBS} ${CUDA_LIBRARIES}
    )

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PUBLIC X11)
endif(UNIX)

add_subdirectory(${SOURCE_DIR}/Commands)
add_subdirectory(${SOURCE_DIR}/Events)
add_subdirectory(${SOURCE_DIR}/ImgHandling)
add_subdirectory(${SOURCE_DIR}/IO)
add_subdirectory(${SOURCE_DIR}/MainHandler)
add_subdirectory(${SOURCE_DIR}/UI)
add_subdirectory(${SOURCE_DIR}/Utilities)
