project (my_qq)
cmake_minimum_required(VERSION 2.8)
include_directories(${PROJECT_SOURCE_DIR}/my_utils)
aux_source_directory(${PROJECT_SOURCE_DIR}/my_utils DIR_MY_UTILS)
add_subdirectory(${PROJECT_SOURCE_DIR}/qq_server ${PROJECT_BINARY_DIR}/qq_server)
add_subdirectory(${PROJECT_SOURCE_DIR}/qq_client ${PROJECT_BINARY_DIR}/qq_client)
