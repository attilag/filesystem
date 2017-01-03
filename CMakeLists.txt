cmake_minimum_required(VERSION 2.8.4)
project(path)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  # Enable C++11 mode on GCC / Clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -U__STRICT_ANSI__")
endif()

add_library("fs"
    "filesystem/path.cpp"
    "filesystem/directory_entry.cpp"

    # Header files (useful in IDEs)
    "filesystem/config.h"
    "filesystem/directory_entry.h"
    "filesystem/file_status.h"
    "filesystem/fwd.h"
    "filesystem/path.h"
    "filesystem/resolver.h"
)

add_executable(path_demo 
	path_demo.cpp 
	filesystem/fwd.h 
	filesystem/path.h 
	filesystem/resolver.h
)
enable_testing()
add_test(tests path_demo)
