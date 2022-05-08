include_directories(${INCLUDE_DIR})

target_sources(${PROJECT_NAME} PUBLIC 
                ${SOURCE_DIR}/Commands/GpuImg/BrightnessCmd.cpp 
                ${SOURCE_DIR}/Commands/GpuImg/ContrastCmd.cpp 
                ${SOURCE_DIR}/Commands/GpuImg/EqualizationCmd.cpp 
                ${SOURCE_DIR}/Commands/GpuImg/InvertionCmd.cpp 
                )

add_subdirectory(${SOURCE_DIR}/Commands/GpuImg/Kernels)
