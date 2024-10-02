/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#ifndef __I_protocolMessage
#define __I_protocolMessage

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "mqtt/async_client.h"
#include "mqtt/client.h"

using jsonType = nlohmann::json;
class IprotocolMessage
{
public:

    //parameterized constructor
    IprotocolMessage(const std::string_view &, const std::string_view &);

    //Non-parameterized constructor
    IprotocolMessage()= default;

    /** @brief - gets mqtt topic
     * @param None - No input parameters
     * @return string - returns string
     */
    std::string getDestination() const;

    /** @brief - gets mqtt message payload
     * @param None - No input parameters
     * @return jsonType - returns json message
     */
    jsonType getPayload() const;

private:
    std::string msgDestination;
    jsonType msgPayload;
};

#endif