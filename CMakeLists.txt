cmake_minimum_required(VERSION 3.16)

project(AnalisisHTML)

add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/src/logic/engine.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/scenes.cpp
    ${PROJECT_SOURCE_DIR}/src/storage/archive.cpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/logic
    ${PROJECT_SOURCE_DIR}/src/graphics
    ${PROJECT_SOURCE_DIR}/src/storage
)