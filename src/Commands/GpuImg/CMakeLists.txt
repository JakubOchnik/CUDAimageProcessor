include_directories(${INCLUDE_DIR})

target_sources(${PROJECT_NAME} PUBLIC 
                ${SOURCE_DIR}/Commands/GpuImg/BrightnessCmd.cpp 
                )

add_subdirectory(${SOURCE_DIR}/Commands/GpuImg/Kernels)
