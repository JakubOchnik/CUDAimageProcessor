include_directories(${INCLUDE_DIR})

target_sources(${PROJECT_NAME} PUBLIC 
                ${SOURCE_DIR}/Utilities/ConfigChecker.cpp 
                ${SOURCE_DIR}/Utilities/GPUControl.cpp 
                ${SOURCE_DIR}/Utilities/GPUInfo.cpp 
                )
