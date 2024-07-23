cmake_minimum_required(VERSION 3.5.0)
project(Sync-Engine VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Sync-Engine main.cpp)

enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
