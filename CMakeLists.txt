cmake_minimum_required(VERSION 3.0)

project("Nibbler")

set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")

include_directories(
	includes/
)

add_subdirectory(sfml)
    find_file(SFML_CMAKE_DIR "SFML/cmake/Modules/FindSFML.cmake")
 
    if (SFML_CMAKE_DIR)
        string(REPLACE "FindSFML.cmake" "" SFML_CMAKE_DIR ${SFML_CMAKE_DIR})
        set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${SFML_CMAKE_DIR}")
    endif()
 
    # find_package(SFML REQUIRED system window graphics audio network) 
find_package(SFML 2 REQUIRED system window graphics audio network)


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
