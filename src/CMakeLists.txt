# Copyright (c) 9-7-2024 Cummins Inc
# 
# This program and the accompanying materials are made
# available under the terms of the Eclipse Public License 2.0
# which is available at https://www.eclipse.org/legal/epl-2.0/
# 
# SPDX-License-Identifier: EPL-2.0

cmake_minimum_required(VERSION 3.5)

add_subdirectory(${PROJECT_NAME})
# Create the executable
SET(APP_NAME "main" CACHE STRING "")
# Fmt libray is not needed for Ubuntu so make it optional
find_package(fmt OPTIONAL_COMPONENTS)

add_executable(${APP_NAME} main.cpp)

if(fmt_FOUND)
    message("Found fmt library")
    target_link_libraries(${APP_NAME} fmt)
else()
    message("Could not find fmt library")
endif()

include_directories(
    ${PROJECT_NAME}/include 
    )

# Set the compiler options

target_link_libraries(${APP_NAME} ${PROJECT_NAME} -pthread -lspdlog -lpaho-mqttpp3 -lpaho-mqtt3a)
install(TARGETS ${APP_NAME} DESTINATION /usr/local/bin)