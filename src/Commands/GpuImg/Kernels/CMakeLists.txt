include_directories(${INCLUDE_DIR})

target_sources(${PROJECT_NAME} PUBLIC 
                ${SOURCE_DIR}/Commands/GpuImg/Kernels/BrightnessKernel.cu 
                ${SOURCE_DIR}/Commands/GpuImg/Kernels/ContrastKernel.cu 
                ${SOURCE_DIR}/Commands/GpuImg/Kernels/EqualizationKernel.cu 
                ${SOURCE_DIR}/Commands/GpuImg/Kernels/InvertionKernel.cu 
                )