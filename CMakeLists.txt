cmake_minimum_required(VERSION 3.22.1)
install(PROGRAMS ${Boost_LIBRARIES} DESTINATION ~/install/lib)

set(CMAKE_CXX_STANDARD 20)

project(chibicc)

FIND_PACKAGE(Boost 1.48 COMPONENTS REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

file(GLOB SOURCE
        "*.h"
        "*.c"
        "include/*.h")

add_executable(chibicc ./main.c  ${SOURCE} ${Boost_LIBRARIES})