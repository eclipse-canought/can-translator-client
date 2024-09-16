
/*
 * main.cpp
 */

/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include "Application.h"

/*
 main function.
*/
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return  RUN_ALL_TESTS();
}