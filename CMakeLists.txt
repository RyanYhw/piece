cmake_minimum_required(VERSION 2.8)
project(OnePiece)

# option 
#option (__TEST__ "USE TEST" ON)
option (__TEST__ "USE TEST" ON)



include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/base)
include_directories(${CMAKE_SOURCE_DIR}/utils)
#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/servers)



set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_VERBOSE_MAKEFILE OFF)


# add source files
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
source_group("Include" FILES ${CURRENT_HEADERS})

# -Werror 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wno-deprecated  \
        -ffunction-sections -W -Wall -pthread -Wno-missing-braces -Wparentheses -std=c++11 -fPIC" )


aux_source_directory(./base    O_BASE)
aux_source_directory(./utils   O_UTILS )
#aux_source_directory(./net     O_NET )

add_subdirectory(base)
add_subdirectory(utils)

add_library(${PROJECT_NAME} SHARED ${O_BASE} ${O_UTILS} ${O_NET})

link_directories(${LIBRARY_OUTPUT_PATH})

target_link_libraries(${PROJECT_NAME} crypto)
#target_link_libraries(${PROJECT_NAME} uuid thrift log4cplus curl ssl gd png  rt thriftnb boost_thread z)
#target_link_libraries(${PROJECT_NAME} tcmalloc friso xapian boost_system mysqlcppconn)

if (__TEST__)
    add_definitions(-D__TEST__)
    add_subdirectory(tests)
endif ()

add_subdirectory(main)

