# Copyright (c) 9-7-2024 Cummins Inc
# 
# This program and the accompanying materials are made
# available under the terms of the Eclipse Public License 2.0
# which is available at https://www.eclipse.org/legal/epl-2.0/
# 
# SPDX-License-Identifier: EPL-2.0
FROM mcr.microsoft.com/vscode/devcontainers/base:0-focal
ARG DEBIAN_FRONTEND=noninteractive
ARG SETUP_DIR="/root"
WORKDIR ${SETUP_DIR}
RUN apt-get update \
     && apt-get install cmake \
                              make \
                              g++ \
                              tcl-dev \
                              clang \
                              git \
                              unzip \
                              wget \
                              gdb \
                              libfmt-dev \
                              libssl-dev -y

##General dependencies
WORKDIR ${SETUP_DIR}
ARG SPD_LOG_VERSION="v1.9.2"
RUN git clone https://github.com/gabime/spdlog.git
WORKDIR ${SETUP_DIR}/spdlog
RUN git checkout ${SPD_LOG_VERSION}
WORKDIR ${SETUP_DIR}/spdlog/build
RUN cmake .. -DSPDLOG_BUILD_SHARED=ON
RUN make && make install

WORKDIR ${SETUP_DIR}
ARG GOOGLE_TEST_VERSION="release-1.11.0"
RUN git clone https://github.com/google/googletest.git
WORKDIR ${SETUP_DIR}/googletest
RUN git checkout ${GOOGLE_TEST_VERSION}
RUN  cmake . && make && make install

WORKDIR ${SETUP_DIR}
ARG PAHO_MQTT_C_VERSION="v1.3.9"
RUN git clone https://github.com/eclipse/paho.mqtt.c.git
WORKDIR  ${SETUP_DIR}/paho.mqtt.c
RUN git checkout ${PAHO_MQTT_C_VERSION}
RUN cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_WITH_SSL=OFF -DPAHO_HIGH_PERFORMANCE=ON
RUN cmake --build build/ --target install

WORKDIR ${SETUP_DIR}
ARG PAHO_MQTT_CPP_VERSION="v1.2.0"
RUN git clone https://github.com/eclipse/paho.mqtt.cpp.git
WORKDIR  ${SETUP_DIR}/paho.mqtt.cpp
RUN git checkout ${PAHO_MQTT_CPP_VERSION}
RUN cmake -Bbuild -H. -DPAHO_BUILD_DOCUMENTATION=FALSE -DPAHO_WITH_SSL=OFF -DPAHO_BUILD_SAMPLES=TRUE
RUN cmake --build build/ --target install

WORKDIR ${SETUP_DIR}
ARG NLOHMANN_VERSION="v3.11.2"
RUN git clone https://github.com/nlohmann/json json --recursive
WORKDIR  ${SETUP_DIR}/json
RUN git checkout ${NLOHMANN_VERSION}
WORKDIR ${SETUP_DIR}/json/build-dir
RUN cmake .. -DMAKE_BUILD_TYPE=Release -DBUILD_TESTING:BOOL=OFF -DJSON_BuildTests=OFF
RUN cmake --build . --config Release --target install -- -j${nproc}

WORKDIR ${SETUP_DIR}
ARG JSON_SCHEMA_VALIDATOR_VERSION=2.2.0
RUN git clone https://github.com/pboettch/json-schema-validator.git
WORKDIR ${SETUP_DIR}/json-schema-validator
RUN git checkout tags/${JSON_SCHEMA_VALIDATOR_VERSION}
WORKDIR ${SETUP_DIR}/json-schema-validator/build-dir
RUN cmake -DBUILD_SHARED_LIBS=ON .. && make && make install
#End General dependencies

WORKDIR ${SETUP_DIR}
RUN rm -rf * && sync
RUN ldconfig