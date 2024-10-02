# Copyright (c) 9-7-2024 Cummins Inc
# 
# This program and the accompanying materials are made
# available under the terms of the Eclipse Public License 2.0
# which is available at https://www.eclipse.org/legal/epl-2.0/
# 
# SPDX-License-Identifier: EPL-2.0

#this dockerfile is intended to work in parallel with Dockerfile, 
#official chnages outside of architecture should be made to both 
FROM opensource-base AS dev
ARG PROJECT_NAME="canought-can-translator-client"
ARG SETUP_DIR="/root"
ARG BUILD_FOLDER="build-dir"
ARG BUILD_TYPE="Release"
WORKDIR ${SETUP_DIR}
COPY src src
COPY test test
COPY CMakeLists.txt .
WORKDIR ${SETUP_DIR}/${BUILD_FOLDER}/${BUILD_TYPE}
RUN cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DAPP_NAME:STRING=${PROJECT_NAME} ../..
RUN make
RUN make install
WORKDIR ${SETUP_DIR}
#Strip libraries 
RUN strip /usr/local/lib/*.so* --strip-all
RUN strip /usr/local/bin/${PROJECT_NAME} --strip-all

ENV RUN_APP=${PROJECT_NAME}

WORKDIR /root
CMD ${RUN_APP}