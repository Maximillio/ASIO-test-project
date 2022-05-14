cmake_minimum_required(VERSION  3.15.0)

set(PROJECT_NAME ASIO_test_project)

project(${PROJECT_NAME})

FILE(GLOB FILES Source/*.cpp)

add_executable(${PROJECT_NAME} ${FILES})

target_include_directories(${PROJECT_NAME} PRIVATE "Include/")
