include_directories(${INCLUDE_DIR})

target_sources(${PROJECT_NAME} PUBLIC 
                ${SOURCE_DIR}/Events/EventHistory.cpp 
                ${SOURCE_DIR}/Events/History.cpp
                )
