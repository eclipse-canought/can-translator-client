# Copyright (c) 9-7-2024 Cummins Inc
# 
# This program and the accompanying materials are made
# available under the terms of the Eclipse Public License 2.0
# which is available at https://www.eclipse.org/legal/epl-2.0/
# 
# SPDX-License-Identifier: EPL-2.0

cmake_minimum_required(VERSION 3.5)

include_directories(./include/)

add_library(${PROJECT_NAME} SHARED
             Application.cpp imqtt-wrapper.cpp iprotocolMessage.cpp observer.cpp translator.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )    
target_link_libraries(${PROJECT_NAME} -lpaho-mqttpp3 -lpaho-mqtt3a)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/lib)