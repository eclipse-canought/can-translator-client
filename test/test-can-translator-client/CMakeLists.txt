# Copyright (c) 9-7-2024 Cummins Inc
# 
# This program and the accompanying materials are made
# available under the terms of the Eclipse Public License 2.0
# which is available at https://www.eclipse.org/legal/epl-2.0/
# 
# SPDX-License-Identifier: EPL-2.0

cmake_minimum_required(VERSION 3.5)
project(test-can-translator-client)

find_package(GTest REQUIRED)

include_directories(
    ${GTEST_INCLUDE_DIRS} 
    ../../src/can-translator-client/include/ 
    )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fprofile-arcs -g -D GTEST" )
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${TEST_BINARY} ${TEST_SOURCES})

add_test(NAME ${TEST_BINARY} COMMAND ${TEST_BINARY})
target_link_libraries(${TEST_BINARY} ${GTEST_LIBRARIES}  pthread can-translator-client -lspdlog -lgmock -lpaho-mqttpp3 -lpaho-mqtt3a)
install(TARGETS ${TEST_BINARY} DESTINATION /usr/local/bin)