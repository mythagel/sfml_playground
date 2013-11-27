CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(sfml_playground)

SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/" )


IF(UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

FIND_PACKAGE(SFML 2 COMPONENTS system window graphics audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(basic basic.cpp)

target_link_libraries(basic ${SFML_LIBRARIES})

