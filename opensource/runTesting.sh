#!/bin/bash
# Copyright (c) 9-7-2024 Cummins Inc
# 
# This program and the accompanying materials are made
# available under the terms of the Eclipse Public License 2.0
# which is available at https://www.eclipse.org/legal/epl-2.0/
# 
# SPDX-License-Identifier: EPL-2.0
if [ "$1" == "" ]; then
    echo "empty argument please give the name of the project"
    echo "pattern expected <component>-<name>"
    exit 1;
fi

#### Global variables ####
export PROJECT="$(echo "$1" | sed -e "s/canought-//g")" #Project pattern expected "<component>-<name>"
export TEST_BIN=test-$PROJECT              #test binary application commonly prepending test to the component name
$TEST_BIN --gtest_catch_exceptions=0
