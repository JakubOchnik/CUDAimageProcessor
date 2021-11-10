include_directories(${INCLUDE_DIR})

target_sources(${PROJECT_NAME} PUBLIC 
                ${SOURCE_DIR}/Commands/GeneralImg/CropCmd.cpp 
                ${SOURCE_DIR}/Commands/GeneralImg/ResizeCmd.cpp
                )
