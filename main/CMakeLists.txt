#-std=c++11
#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
#INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/include)


aux_source_directory(. SRC_LIST)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(teach ${SRC_LIST})


#TARGET_LINK_LIBRARIES(${PROJECT_NAME} jemalloc pthread rt event thrift thriftnb boost_thread log4cplus OnePiece)
TARGET_LINK_LIBRARIES(teach OnePiece)


