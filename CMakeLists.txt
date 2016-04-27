cmake_minimum_required(VERSION 2.8)
project(fastcginetworkconfig CXX)

# use cmake -DCMAKE_BUILD_TYPE=Release .. to build release

if(CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build/lib")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-deprecated")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(FCGI REQUIRED)
if(FCGI_FOUND)
    INCLUDE_DIRECTORIES(${FCGI_INCLUDE_DIRS})
endif()

INCLUDE_DIRECTORIES(
	src/${PROJECT_NAME}/
	src/json/src/
)

add_library(
	${PROJECT_NAME}_lib

	STATIC

	src/${PROJECT_NAME}/${PROJECT_NAME}.cpp
)

target_link_libraries(
	${PROJECT_NAME}_lib

	fcgi
	pthread
)

# urlmanager
add_executable(
	${PROJECT_NAME}
	
	src/${PROJECT_NAME}/main.cpp
)

target_link_libraries(
	${PROJECT_NAME} 

	${PROJECT_NAME}_lib
)

if (CMAKE_BUILD_TYPE MATCHES DEBUG)
	message("tests enabled")

	add_subdirectory(src/gtest/googletest)
	add_subdirectory(src/${PROJECT_NAME}/tests)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION "bin")
