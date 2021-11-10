include_directories(${INCLUDE_DIR})

target_sources(${PROJECT_NAME} PUBLIC 
                ${SOURCE_DIR}/Commands/BaseCommand.cpp 
                ${SOURCE_DIR}/Commands/BaseEditCmd.cpp
                ${SOURCE_DIR}/Commands/BaseGenericCmd.cpp
                )

#add_subdirectory(${SOURCE_DIR}/Commands/CpuImg)
add_subdirectory(${SOURCE_DIR}/Commands/GeneralImg)
#add_subdirectory(${SOURCE_DIR}/Commands/GpuImg)
add_subdirectory(${SOURCE_DIR}/Commands/Ui)
#add_subdirectory(${SOURCE_DIR}/Commands/Utils)
