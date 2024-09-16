# Copyright (c) 9-7-2024 Cummins Inc
# 
# This program and the accompanying materials are made
# available under the terms of the Eclipse Public License 2.0
# which is available at https://www.eclipse.org/legal/epl-2.0/
# 
# SPDX-License-Identifier: EPL-2.0

project(can-translator-client)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a" )
set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH} /usr/local/lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TEST_BINARY test-${PROJECT_NAME})

if(ENABLE_TESTING)
    add_subdirectory(src)
    add_subdirectory(test)
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -D GTEST" )
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
    endif()
else()
    add_subdirectory(src)
endif()