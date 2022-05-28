cmake_minimum_required(VERSION  3.15.0)

set(PROJECT_NAME ASIO_test_project)

project(${PROJECT_NAME})

set(FIRST_EXEC Client)
set(SECOND_EXEC Server)

set(FILES Source/main.cpp)
set(FILES_ADD Source/main_add.cpp)

add_executable(${FIRST_EXEC} ${FILES})

target_include_directories(${FIRST_EXEC} PRIVATE "Include/")

add_executable(${SECOND_EXEC} ${FILES_ADD})

target_include_directories(${SECOND_EXEC} PRIVATE "Include/")
