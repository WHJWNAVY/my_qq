#include_directories(${PROJECT_SOURCE_DIR}/my_utils)
#aux_source_directory(${PROJECT_SOURCE_DIR}/my_utils DIR_MY_UTILS) 
aux_source_directory(${PROJECT_SOURCE_DIR}/qq_client DIR_QQ_CLIENT)
add_executable(client_qq ${DIR_QQ_CLIENT} ${DIR_MY_UTILS})
