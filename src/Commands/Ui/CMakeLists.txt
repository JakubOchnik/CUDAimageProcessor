include_directories(${INCLUDE_DIR})

target_sources(${PROJECT_NAME} PUBLIC 
                ${SOURCE_DIR}/Commands/Ui/ClearCmd.cpp
                ${SOURCE_DIR}/Commands/Ui/HelpCmd.cpp
                ${SOURCE_DIR}/Commands/Ui/HistoryCmd.cpp
                ${SOURCE_DIR}/Commands/Ui/LoadCmd.cpp
                ${SOURCE_DIR}/Commands/Ui/QuitCmd.cpp
                ${SOURCE_DIR}/Commands/Ui/RedoCmd.cpp
                ${SOURCE_DIR}/Commands/Ui/UndoCmd.cpp
                ${SOURCE_DIR}/Commands/Ui/SaveCmd.cpp
                ${SOURCE_DIR}/Commands/Ui/ShowCmd.cpp
                )
