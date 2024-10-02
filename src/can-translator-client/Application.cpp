/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/

#include "include/Application.h"

using namespace std;

void Application::Init()
{
     // Call example function ReadUDSParameter() or any other translator API function here after passing input arguments.
     //Modify function/class as per need. 
}

bool Application::ReadUDSParameter(const std::vector<std::string> &did)
{
    translator::uds::response::ReadDataByIdentifier udsReadResponse = getcommunicationLibPtr()->getUDSPtr()->ReadByDataIdentifier(did);

    return true;
}

