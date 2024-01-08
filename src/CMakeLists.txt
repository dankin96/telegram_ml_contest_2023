cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(tglang VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
find_library(catboost ${CMAKE_CURRENT_SOURCE_DIR}/../resources/libcatboostmodel.so)
add_library(tglang SHARED tglang.cpp)
#add_executable(tglang tglang.cpp)
add_custom_command(TARGET tglang POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/../resources $<TARGET_FILE_DIR:tglang>/resources)
target_include_directories(tglang PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tglang ${CMAKE_CURRENT_SOURCE_DIR}/../resources/libcatboostmodel.so)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
