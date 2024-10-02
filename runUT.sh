#!/bin/sh

# Copyright (c) 9-7-2024 Cummins Inc
# 
# This program and the accompanying materials are made
# available under the terms of the Eclipse Public License 2.0
# which is available at https://www.eclipse.org/legal/epl-2.0/
# 
# SPDX-License-Identifier: EPL-2.0

export opensrc_component=canought-can-translator-client #update this variable based on the component name
docker rm -f $opensrc_component-test
docker compose -f opensource/docker-compose-ut.yml up --force-recreate --build

if [ 0 -eq $? ] ; then
    echo "--- Success running UT Project $opensrc_component ---"
else
    echo "Error while running UT project $opensrc_component"
fi

