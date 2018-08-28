include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#aux_source_directory(. SRC_LIST)#

#link_directories(/usr/lib)

#add_executable(test-onepiece ${SRC_LIST})
#TARGET_LINK_LIBRARIES(test-onepiece gtest friso OnePiece)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -Wno-deprecated  \
        -ffunction-sections -W -Wall -pthread -Wno-missing-braces -Wparentheses -std=c++11 -DGTEST_USE_OWN_TR1_TUPLE=0" )



add_subdirectory(test)
add_subdirectory(gtest-1.7.0)
