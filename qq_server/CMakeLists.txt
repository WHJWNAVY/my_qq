#include_directories(${PROJECT_SOURCE_DIR}/my_utils)
#aux_source_directory(${PROJECT_SOURCE_DIR}/my_utils DIR_MY_UTILS) 
aux_source_directory(${PROJECT_SOURCE_DIR}/qq_server DIR_QQ_SERVER)
add_executable(server_qq ${DIR_QQ_SERVER} ${DIR_MY_UTILS})
