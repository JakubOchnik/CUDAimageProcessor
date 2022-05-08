include_directories(${INCLUDE_DIR})

target_sources(${PROJECT_NAME} PUBLIC 
                ${SOURCE_DIR}/ImgHandling/ImgInfo.cpp 
                ${SOURCE_DIR}/ImgHandling/ImgLoader.cpp 
                )
