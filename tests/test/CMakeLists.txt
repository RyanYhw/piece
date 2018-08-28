#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(. SRC_LIST)#

#link_directories(/usr/lib)

add_executable(test-onepiece ${SRC_LIST})
TARGET_LINK_LIBRARIES(test-onepiece gtest OnePiece)
