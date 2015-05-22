cmake_minimum_required(VERSION 3.0)

project("Nibbler")

set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")

include_directories(
	includes/
)

# add_subdirectory(sfml)

# link_directories()
# target_link_libraries()

file(
	GLOB_RECURSE

	"SOURCE_FILES"

	src/*

	includes/*
)

add_executable(
	nibbler

	${SOURCE_FILES}
)

# target_link_libraries(nibbler ${CMAKE_DL_LIBS})
