cmake_minimum_required(VERSION 3.15)
project(SoExceptions)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++ -static-libgcc -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/script.ld")

#set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
#set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++ -static-libgcc")

#set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
#set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++ -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/script.ld")

#set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc")
#set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/script.ld")

add_executable(main main.cpp)
target_link_libraries(main ${CMAKE_DL_LIBS})

add_library(plugin-catch SHARED plugin-catch.cpp)
add_library(plugin-throw SHARED plugin-throw.cpp)
