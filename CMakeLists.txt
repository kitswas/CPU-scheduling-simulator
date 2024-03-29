cmake_minimum_required(VERSION 3.16)
project(CPP_project)

set(CMAKE_CXX_STANDARD 17)

# Some compiler flags for GCC and Clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU") 
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Wold-style-cast -Wnull-dereference")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s -DNDEBUG")
endif()

set(SOURCES
	src/main.cpp
	src/process.cpp
	src/process_creator.cpp
	src/FCFS.cpp
	src/min_heap.cpp
	src/simulator.cpp
	src/printer.cpp
	src/RR.cpp
	src/rbtree.cpp
	src/CFS.cpp)

add_executable(executable ${SOURCES})
