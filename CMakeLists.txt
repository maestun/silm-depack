cmake_minimum_required(VERSION 3.0.0)
project(silmarils-unpacker VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(silmarils-unpacker src/debug.c 
               src/main.c src/platform.c 
               src/unpack.c src/utils.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
