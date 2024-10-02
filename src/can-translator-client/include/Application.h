/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#pragma once

#include <map>
#include <queue>
#include <thread>
#include "mqtt/async_client.h"
#include "mqtt/client.h"
#include "imqtt-wrapper.h"
#include "apiconstants.h"
#include "globalconfig.h"
#include "observer.h"


class Application : public Observer
{
public:

    //Application constructor
    explicit Application(std::shared_ptr<InterContainerMessenger> Client) : Observer(Client){};

    //default application destructor
    ~Application()  = default;

    /** @brief Init method to execute all initialization operations.
     * @return void
     */

    void Init() override;

    /** @brief Read UDS parameter from the ECM
     * @param did values to be fetched - std::vector<std::string>,std::string
     * @return bool - Returns true
     */

    bool ReadUDSParameter(const std::vector<std::string> &did);

};
